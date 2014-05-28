# -*- coding: utf-8 -*-
'''
Created on 2014-4-28

@author: cheng.li
'''

from CAL import *
import pandas as pd

if __name__ == '__main__':
    
    curveCandidate = pd.read_excel(u'基准债券.xls', 'Sheet1')
    dateList = curveCandidate['date'].unique()
    settlementDays = 1
    
    yieldCurves = {}
    totalRates = []
    
    for date in dateList:
        instruments = curveCandidate[curveCandidate['date'] == date]
        timeStamp = pd.Timestamp(date)
        tmp = timeStamp.date()
        evalDate = Date(tmp.day, tmp.month, tmp.year)
        
        Settings.instance().setEvaluationDate(evalDate)
        
        ratesHelper = []
        index = instruments.index
        for inst in index:
            tmp = instruments.ix[inst]['tenor']
            tenor = PeriodParser.parse(str(tmp))
            maturityDate = instruments.ix[inst]['maturity']
            maturityDate = Date(maturityDate.day, maturityDate.month, maturityDate.year)
            startDate = maturityDate - tenor
            coupon = instruments.ix[inst]['coupon'] / 100.0
            yieldOfBond = instruments.ix[inst]['yield'] / 100.0
            
            timeToMaturity = (maturityDate - evalDate) / 365.0
            if timeToMaturity < 1.0:
                compounding = Simple
            else:
                compounding = Compounded
            frequency = instruments.ix[inst]['freq']
            
            if frequency == 1:
                frequency = Annual
            elif frequency == 2:
                frequency = Semiannual
            else:
                raise Exception("")
            
            tenor = Period(frequency)
            
            dc = ActualActual(ActualActual.ISMA)
            
            # Start build the bond and convert yield to clean price
            bondObj = CTBFixedBond(issueDate = startDate,
                                   settlementDays = settlementDays,
                                   faceAmount = 100.0,
                                   startDate = startDate,
                                   maturity = maturityDate,
                                   tenor = tenor,
                                   coupons = [coupon],
                                   accrualDayCounter = dc)
            
            cleanPrice = bondObj.cleanPrice(yieldOfBond,
                                            dc, 
                                            compounding,
                                            frequency)
            
            # Build bond rate helper based on clean price
            quote = SimpleQuote(cleanPrice)
            quoteHandler = QuoteHandle(quote)
            
            bondHelper = CTBFixedBondHelper(quoteHandler,
                                            settlementDays,
                                            100.0,
                                            startDate,
                                            maturityDate,
                                            tenor,
                                            [coupon],
                                            dc)
            
            ratesHelper.append(bondHelper)
            
        yieldCurve = PiecewiseFlatForward(evalDate,
                                        ratesHelper,
                                        dc)
    
        yieldCurves[evalDate] = yieldCurve
        
        # Calculate benchmark curve points
        tenors = ['1Y', '2Y', '3Y', '4Y', '5Y', '6Y', '7Y', '8Y', '9Y']
        dates = [evalDate + Period(x) for x in tenors]
        rates = {}
        rates['date'] = date
        for tenor, date in zip(tenors,dates):
            rate = yieldCurve.zeroRate(date, dc, Compounded, Annual)
            rates[tenor] = rate.rate()
        
        totalRates.append(rates)
        
        
    resDF = pd.DataFrame(totalRates)
    resDF.to_excel(u'收益率曲线.xls')