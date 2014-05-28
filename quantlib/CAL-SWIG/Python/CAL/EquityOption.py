# -*- coding: utf-8 -*-
'''
Created on 2014-3-17

@author: cheng.li
'''

from CAL import *
import math
import numpy as np
import pandas as pd
import FunctionTools

def __BSMPrice__(optionType, strike, spot, riskFree, dividend, volatility, maturity):
    if maturity == 0.0:
        raise Exception("#maturity cant be 0!")
    
    calOptionType = Option.Call
    if optionType == -1:
        calOptionType = Option.Put
        
    calForward = math.exp((riskFree-dividend)*maturity) * spot
    calStrike = strike
    calStdDev = math.sqrt(maturity) * volatility
    calDiscount = math.exp(-riskFree*maturity)
    myPayoff = PlainVanillaPayoff(calOptionType, calStrike)
    calculator =  BlackCalculator(myPayoff, 
                               calForward, 
                               calStdDev,
                               calDiscount)
    
    
    value = calculator.value()
    delta = calculator.delta(spot)
    gamma = calculator.gamma(spot)
    vega = calculator.vega(maturity)
    return value, delta, gamma, vega

def __BaroneAdesiWhaleyApproximation__(optionType, strike, spot, riskFree, dividend, volatility, maturity):
    if maturity == 0.0:
        raise Exception("#maturity cant be 0!")
    
    calOptionType = Option.Call
    if optionType == -1:
        calOptionType = Option.Put
        
    calStrike = strike
    myPayoff = PlainVanillaPayoff(calOptionType, calStrike)
    
    myQuote = SimpleQuote(spot)
    spotHandle = QuoteHandle(myQuote)
 
    todayDate = Date.todaysDate()
    Settings.instance().setEvaluationDate(todayDate)
    
    yieldTermStructure = FlatForward(0, NullCalendar(), riskFree, ActualActualNoLeap(), Continuous);
    yieldHandle = YieldTermStructureHandle(yieldTermStructure)
    
    divTermStructure = FlatForward(0, NullCalendar(), dividend, ActualActualNoLeap(), Continuous);
    divHandle = YieldTermStructureHandle(divTermStructure)
    
    volQuote = SimpleQuote(volatility)
    volQuoteHandler = QuoteHandle(volQuote)
    volTermstructure = BlackConstantVol(0, NullCalendar(), volQuoteHandler, ActualActualNoLeap())
    volHandle = BlackVolTermStructureHandle(volTermstructure)
    
    BSMProcess = GeneralizedBlackScholesProcess(spotHandle, divHandle, yieldHandle, volHandle)
    
    pricingEngine = BaroneAdesiWhaleyEngine(BSMProcess)
    exDate = todayDate + Period(int(maturity * 365 + 0.5), Days)
    exercise = AmericanExercise(todayDate, exDate)
    optionTmp = VanillaOption(myPayoff, exercise)
    
    optionTmp.setPricingEngine(pricingEngine)
    
    NPV = optionTmp.NPV()
    
    # Using finite difference to get greeks
    basisValue = spot * 0.0001
    myQuote.setValue(spot + basisValue)
    NPVP01 = optionTmp.NPV()
    
    myQuote.setValue(spot - basisValue)
    NPVM01 = optionTmp.NPV()
    
    # calculated delta, gamma and vega
    delta = (NPVP01 - NPVM01) / 2.0 / basisValue
    gamma = (NPVP01 - 2.0 * NPV + NPVM01) / (basisValue ** 2)
    
    myQuote.setValue(spot)
    basisValue = volatility * 0.0001
    volQuote.setValue(volatility + basisValue)
    NPVP01 = optionTmp.NPV()
    volQuote.setValue(volatility - basisValue)
    NPVM01 = optionTmp.NPV()
    vega = (NPVP01 - NPVM01) / 2.0 / basisValue
    
    return NPV, delta, gamma, vega
    

def BaroneAdesiWhaleyPrice(optionType, strike, spot, riskFree, dividend, volatility, maturity):
    '''
    BaroneAdesi-Whaley 美式期权逼近公式
    Barone-Adesi, G.; R. Whaley (1987). Efficient Analytic Approximation of American Option Values. Journal of Derivatives 42 (2): 301–320
    
    Underlying Process
    \[
        dS = (r - d)S dt + \sigma * d W(t), t > 0
    \]
    
    Input:
    optionType -- 期权类型，1 for CALL或者 -1 for PUT
    strike     -- 行权价格
    spot       -- 标的股票价格
    riskFree   -- 无风险利率
    dividend   -- 股票红利率
    volatility -- 波动率
    maturity   -- 到期时间（年）
    
    Output: 期权价格
    
    '''
    myFunc = np.frompyfunc(__BaroneAdesiWhaleyApproximation__, 7, 4)
    optionPrice = myFunc(optionType, strike, spot, riskFree, dividend, volatility, maturity)
    
    return FunctionTools.__formatResult__(optionPrice, ['price', 'delta', 'gamma', 'vega'])
    
def BSMPrice(optionType, strike, spot, riskFree, dividend, volatility, maturity):
    '''
    Black-Scholes-Merton 期权定价公式
    Black, Fischer; Myron Scholes (1973). The Pricing of Options and Corporate Liabilities. Journal of Political Economy 81 (3): 637–654
    
    Underlying Process
    \[
        dS = (r - d)S dt + \sigma * d W(t), t > 0
    \]
    
    Input:
    optionType -- 期权类型，1 for CALL或者 -1 for PUT
    strike     -- 行权价格
    spot       -- 标的股票价格
    riskFree   -- 无风险利率
    dividend   -- 股票红利率
    volatility -- 波动率
    maturity   -- 到期时间（年）
    
    Output: 期权价格
    
    '''
    myFunc = np.frompyfunc(__BSMPrice__, 7, 4)
    optionPrice = myFunc(optionType, strike, spot, riskFree, dividend, volatility, maturity)
    
    return FunctionTools.__formatResult__(optionPrice, ['price', 'delta', 'gamma', 'vega'])
    
    
def __BSMImpliedVolatity__(optionType, strike, spot, riskFree, dividend, maturity, quotePrice):
    
    if maturity == 0.0:
        raise Exception("#maturity cant be 0!")
    
    calOptionType = Option.Call
    if optionType == -1:
        calOptionType = Option.Put
        
    calForward = math.exp((riskFree-dividend)*maturity) * spot
    calStrike = strike
    calDiscount = math.exp(-riskFree*maturity)
    calDisplacement = 0.0
    stdDev = BlackFormula.blackFormulaImpliedStdDev(calOptionType, 
                                         calStrike,
                                         calForward,
                                         quotePrice,
                                         calDiscount,
                                         calDisplacement,
                                         nullDouble(),
                                         1e-10)
    return stdDev / math.sqrt(maturity)

def BSMImpliedVolatity(optionType, strike, spot, riskFree, dividend, maturity, quotePrice):
    '''
    Black-Scholes-Merton Implied volatility 期权隐含波动率
    Black, Fischer; Myron Scholes (1973). The Pricing of Options and Corporate Liabilities. Journal of Political Economy 81 (3): 637–654
    
    Underlying Process
    \[
        dS = (r - d)S dt + \sigma * d W(t), t > 0
    \]
    
    Input:
    optionType -- 期权类型，1 for CALL或者 -1 for PUT
    strike     -- 行权价格
    spot       -- 标的股票价格
    riskFree   -- 无风险利率
    dividend   -- 股票红利率
    maturity   -- 到期时间（年）
    quotePrice -- 期权报价
    
    Output: 期权隐含波动率
    
    '''
    myFunc = np.frompyfunc(__BSMImpliedVolatity__, 7, 1)
    res = myFunc(optionType, strike, spot, riskFree, dividend, maturity, quotePrice)
    return FunctionTools.__formatResult__(res, ['vol'])

if __name__ == '__main__':
    optionType = -1
    strike = [100.0,200,300]
    spot = 100.0
    riskFree = 0.0
    dividend = 0.0
    volatility = 0.25
    maturity = 1.0
    
    strikeDF = pd.DataFrame({'strike':strike})
    print strikeDF
    
    price = BSMPrice(optionType, 
             strikeDF, 
             spot,
             riskFree,
             dividend,
             volatility,
             maturity)
    print price
    
    print BSMImpliedVolatity(optionType, 
             strike, 
             spot,
             riskFree,
             dividend,
             maturity,
             price['price'])
    
    print BaroneAdesiWhaleyPrice(optionType, 
             strike, 
             spot,
             riskFree,
             dividend,
             volatility,
             maturity)