# -*- coding: utf-8 -*-
'''
Created on 2014-3-3

@author: cheng.li
'''

import numpy as np
from CAL import *
import pandas as pd
import datetime as dt
import datetime
from collections import defaultdict

def toCALDate(timeStamp):
    return Date(timeStamp.day, timeStamp.month, timeStamp.year)

def toPYDate(calDate):
    return dt.date(calDate.year(), calDate.month(), calDate.dayOfMonth())

def stringToCALFrequency(stringFrequency):
    upperCase = stringFrequency.upper()
    if upperCase == 'M':
        return 12
    elif upperCase == 'S':
        return 2
    elif upperCase == 'Q':
        return 4
    elif upperCase == 'Y':
        return 1
    else:
        raise Exception('Not known frequency currently') 

def findLastPaymentDate(period, maturity, valuationDate, startDate):
    loopDate = maturity
    while loopDate >= valuationDate and loopDate >= startDate:
        loopDate = loopDate - period
        
    if loopDate<startDate:
        loopDate = startDate
    return loopDate

# Spread is by bps
# currently can't handle bonds whose frequency are short than month
def getLoanCashFlow(startDate, maturity, coupon, faceAmount, frequency, valuationDate, spread = 0.0):
    
    lastPaymentDate = findLastPaymentDate(Period(int(12/frequency), Months), maturity, valuationDate, startDate)
    
    remainingPeriod = (maturity.year() - lastPaymentDate.year()) * 12 + maturity.month() - lastPaymentDate.month()
    
    loanAsBond = AmortizingFixedRateBond(0, NullCalendar(), faceAmount, lastPaymentDate, Period(remainingPeriod, Months),
                                         int(frequency), coupon/100.0 + spread / 10000.0, ActualActual(ActualActual.ISMA), Unadjusted)
    
    cashFlows = loanAsBond.cashflows()
                                     
    interestCashFlows = []
    principleCashFlows = []
    for i in xrange(len(cashFlows)):
        cashflow = cashFlows[i]
        if i%2:
            principleCashFlows.append((toPYDate(cashflow.date()), cashflow.amount()))
        else:
            interestCashFlows.append((toPYDate(cashflow.date()),cashflow.amount()))
    return (interestCashFlows, principleCashFlows)

# Collect the loan level cash flows
def collectLoanCashFlows(loanData, scenario):
    allCashFlows = []
    startDates = loanData[u'放款日'].apply(toCALDate)
    maturities = loanData[u'到期日'].apply(toCALDate)
    coupons = loanData[u'现行行利率'].astype('float64')
    faceAmounts = loanData[u'未偿本金余额'].astype('float64')
    frequencies = loanData[u'还款频率'].apply(stringToCALFrequency)
    for index in loanData.index:
        allCashFlows.append(getLoanCashFlow(startDates[index],
                                        maturities[index],
                                        coupons[index],
                                        faceAmounts[index],
                                        frequencies[index],
                                        valuationDate, scenario))
    return allCashFlows


# Aggregate cash flow into total colleteral
def aggerateCashFlowToColletral(loanCashFlows):
    totalInterestCashFlow = defaultdict(np.float64)
    totalPrincipleCashFlow = defaultdict(np.float64)

    for cashflowAll in loanCashFlows:
        interest = cashflowAll[0]
        principle = cashflowAll[1]
    
        for cashflow in interest:
            key = cashflow[0]
            totalInterestCashFlow[key] += cashflow[1]
        for cashflow in principle:
            key = cashflow[0]
            totalPrincipleCashFlow[key] += cashflow[1]

    return (totalInterestCashFlow, totalPrincipleCashFlow)

# Aggregate colleteral cash flow by frequency
# Only workable for frequency bigger than Weekly
def aggregateCashFlowByFrequency(cashflows, frequency):
    # suppose cashflows is a dictionay of pair date and amount
    newkeys = cashflows.keys()
    newkeys.sort()
    
    firstDate = toCALDate(newkeys[0])
    lastDate = toCALDate(newkeys[-1])
    
    startEnd = firstDate
    lastEnd = firstDate
    if frequency <= Monthly:
        startEnd = Date.endOfMonth(firstDate)
        lastEnd = Date.endOfMonth(lastDate)
    else:
        startEnd = Date.nextWeekday(firstDate,Friday)
        lastEnd = Date.nextWeekday(lastDate,Friday)
        
    
    freCashFlow = {}
    while lastEnd >= startEnd:
        freCashFlow[toPYDate(lastEnd)] = 0.0
        lastEnd -= Period(frequency)
        if frequency <= Monthly:
            lastEnd = Date.endOfMonth(lastEnd)
    
    pillarDates = freCashFlow.keys()
    pillarDates.sort()
    
    startCount = 0
    
    for key in newkeys:
        if key <= pillarDates[startCount]:        
            freCashFlow[pillarDates[startCount]] += cashflows[key]
        else:
            startCount += 1
            while pillarDates[startCount] < key and pillarDates[startCount] < key:
                startCount += 1
            freCashFlow[pillarDates[startCount]] += cashflows[key]
    
    return freCashFlow


def colletralCashFlowsToDF(principleByFrequency, interestByFrequency):
    mykeys = principleByFrequency.keys()
    mykeys = np.array(mykeys)
    report = pd.DataFrame({'Principle':principleByFrequency.values(), 'Interest':interestByFrequency.values()}, index = mykeys)
    return report.sort_index()

def getDefaultModels(valuationDate, poolSize, hazardRate = 0.1, correlation = 0.2):
    Settings.instance().setEvaluationDate(valuationDate)
    
    hazardLambda = hazardRate
    hazardQuote = SimpleQuote(hazardLambda)
    hazardHandler = QuoteHandle(hazardQuote)
    ptr = FlatHazardRate(valuationDate, hazardHandler, ActualActual(ActualActual.ISMA))
    
    basket = DefaultProbabilityTermStructureVec()
    issuers = IssuerVec()
    probabilities = key_curve_pair_vec()
    pool = Pool()
    names = StrVector()
    probabilities.push_back(key_curve_pair(NorthAmericaCorpDefaultKey(EURCurrency(), SecDom, Period(0, Weeks), 10.), 
                      DefaultProbabilityTermStructureHandle(ptr)))
    
    for i in xrange(poolSize):
        o = "Issuer-" + str(i)
        names.push_back(o)
        basket.push_back(DefaultProbabilityTermStructureHandle(ptr))
        issuers.push_back(Issuer(probabilities))
        pool.add(names.back(), issuers.back())
        
    correlationQuote = SimpleQuote(correlation)
    correlationHandler= QuoteHandle(correlationQuote)
    
    pGaussianCopula = OneFactorGaussianCopula(correlationHandler)
    hCopula = RelinkableOneFactorCopulaeHandle(pGaussianCopula)
    defaultProbKeyVec = DefaultProbKeyVec(poolSize, NorthAmericaCorpDefaultKey(EURCurrency(), SecDom))
    myModel = GaussianRandomDefaultModel(pool, defaultProbKeyVec, hCopula, 1e-6, 42)
    return myModel


def getDefaultTimes(myModel, maxHorizontal):
    myModel.nextSequence(maxHorizontal)
    myPool = myModel.pool()
    defaultTimes = [myPool.getTime(name) for name in myPool.names()]
    return defaultTimes

def truncateCashFlows(valuationDate, allCashFlows, defaultTimes, survival = 0.5):
    truncatedAllCashFlows = []
    for index, (interestCashFlows, principleCashFlows) in enumerate(allCashFlows):
        defualtInYears = defaultTimes[index]
        defaultInDays = int(defualtInYears*365)
        defaultDate = valuationDate + Period(defaultInDays, Days)
        (truncatedICF, truncatedPCF) = defGetLoanTruncated(interestCashFlows, principleCashFlows, toPYDate(defaultDate), survival)
        truncatedAllCashFlows.append((truncatedICF, truncatedPCF))
    return truncatedAllCashFlows

def defGetLoanTruncated(ICF, PCF, defaultDate, survival):
    truncatedICF = ICF[:]
    truncatedPCF = PCF[:]
    for index, (cfDate, cfAmount) in enumerate(truncatedICF):
        if cfDate >= defaultDate:
            truncatedICF[index] = (cfDate, 0.0);
            
    for index, (cfDate, cfAmount) in enumerate(truncatedPCF):
        if cfDate >= defaultDate:
            truncatedPCF[index] = (cfDate, cfAmount * survival)
    
    return (truncatedICF, truncatedPCF)

if __name__ == '__main__':
    
    valuationDate = Date(1, 1, 2014)

    loanData = pd.read_excel(r'Update20131231_995MM Asset Pool Details - Minsheng .xls', 'Sheet1')
    writer = pd.ExcelWriter('Scenario.xls')
    
    # Rates scenarios
    scenarios = [0, -25, -50, -75, 25, 50, 75]
    
    # MC parameters
    simulations = 1
        
    print "Loan size: " + str(len(loanData))
    print "Number of Paths: " + str(simulations)
    
    hazardRate = 0.0
    correlation = 0.2
    survival = 0.5
    
    print "Hazard default rate: " + str(hazardRate)
    print "Gaussion copula corr.: " + str(correlation)
    print "Survival(%): " + str(survival * 100)
    
    
    
    for scenario in scenarios:
        print "\nRate Scenario " + str(scenario) + "(bps) Simualtion starts: " + str(datetime.datetime.now())
        # Build default model
        defatultModel = getDefaultModels(valuationDate, len(loanData), hazardRate = hazardRate, correlation = correlation)
        
        # Get loan level cash flows
        allCashFlows = collectLoanCashFlows(loanData, scenario)
        
        cashFlowDFSimulateSum = None

        for simulate in xrange(simulations):
            #print "simulate: " + str(simulate + 1)
            defaultTimes = getDefaultTimes(defatultModel, maxHorizontal = 5)
            truncatedAllCashFlows = truncateCashFlows(valuationDate, allCashFlows, defaultTimes, survival = survival)
    
            # Get colletral level cash flows
            (totalInterestCashFlow, totalPrincipleCashFlow) = aggerateCashFlowToColletral(truncatedAllCashFlows)
        
            # Cash flow report by frequency (e.g. monthly, quarterly, weekly
            principleByFrequency = aggregateCashFlowByFrequency(totalPrincipleCashFlow, Monthly)
            interestByFrequency = aggregateCashFlowByFrequency(totalInterestCashFlow, Monthly)
            cashFlowDF = colletralCashFlowsToDF(principleByFrequency, interestByFrequency)
            
            if simulate == 0:
                cashFlowDFSimulateSum = cashFlowDF
            else:
                cashFlowDFSimulateSum = cashFlowDFSimulateSum + cashFlowDF
            
        cashFlowDFSimulateSum = cashFlowDFSimulateSum / simulations    
        cashFlowDFSimulateSum.to_excel(writer, str(scenario))
        
        print "Rate Scenario " + str(scenario) + "(bps) Simualtion ends: " + str(datetime.datetime.now())
        
    writer.save()