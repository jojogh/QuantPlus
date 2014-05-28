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
def buildLoan(startDate, maturity, coupon, faceAmount, frequency, valuationDate, spread = 0.0):
    
    lastPaymentDate = findLastPaymentDate(Period(int(12/frequency), Months), maturity, valuationDate, startDate)
    
    remainingPeriod = (maturity.year() - lastPaymentDate.year()) * 12 + maturity.month() - lastPaymentDate.month()
    
    loanAsBond = AmortizingFixedRateBond(0, NullCalendar(), faceAmount, lastPaymentDate, Period(remainingPeriod, Months),
                                         int(frequency), coupon/100.0 + spread / 10000.0, ActualActual(ActualActual.ISMA), Unadjusted)
    #loanAsBond = CTBFixedBond(lastPaymentDate, 0, 100.0, lastPaymentDate, lastPaymentDate + Period(remainingPeriod, Months), Period(1, Months), [0.05])
    return loanAsBond

# Collect the loan level cash flows
def buildLoansPool(loanData, scenario):
    allLoans = []
    startDates = loanData[u'放款日'].apply(toCALDate)
    maturities = loanData[u'到期日'].apply(toCALDate)
    coupons = loanData[u'现行行利率'].astype('float64')
    faceAmounts = loanData[u'未偿本金余额'].astype('float64')
    frequencies = loanData[u'还款频率'].apply(stringToCALFrequency)
    for index in loanData.index:
        allLoans.append(buildLoan(startDates[index],
                                        maturities[index],
                                        coupons[index],
                                        faceAmounts[index],
                                        frequencies[index],
                                        valuationDate, scenario))
    return LoansPool(allLoans)

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

# Aggregate colleteral cash flow by frequency
# Only workable for frequency bigger than Weekly
def aggregateCashFlowByFrequency(cashflows, frequency):
    # suppose cashflows is a vector of pair date and amount
    newkeys = []
    for cf in cashflows:
        newkeys.append(cf.date())
    
    firstDate = newkeys[0]
    lastDate = newkeys[-1]
    
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
    
    for cf in cashflows:
        key = toPYDate(cf.date())
        amount = cf.amount()
        if key <= pillarDates[startCount]:        
            freCashFlow[pillarDates[startCount]] += amount
        else:
            startCount += 1
            while pillarDates[startCount] < key and pillarDates[startCount] < key:
                startCount += 1
            freCashFlow[pillarDates[startCount]] += amount
    
    return freCashFlow

def colletralCashFlowsToDF(principleByFrequency, interestByFrequency):
    mykeys = principleByFrequency.keys()
    mykeys = np.array(mykeys)
    report = pd.DataFrame({'Principle':principleByFrequency.values(), 'Interest':interestByFrequency.values()}, index = mykeys)
    return report.sort_index()

if __name__ == '__main__':
    
    valuationDate = Date(1, 1, 2014)

    loanData = pd.read_excel(r'Update20131231_995MM Asset Pool Details - Minsheng .xls', 'Sheet1')
    writer = pd.ExcelWriter('Scenario.xls')
    
    # Rates scenarios
    scenarios = [0, -25, -50, -75, 25, 50, 75]
    
    # MC parameters
    simulations = 100
        
    print "Loan size: " + str(len(loanData))
    print "Number of Paths: " + str(simulations)
    
    hazardRate = 0.1
    correlation = 0.2
    survival = 0.5
    
    print "Hazard default rate: " + str(hazardRate)
    print "Gaussion copula corr.: " + str(correlation)
    print "Survival(%): " + str(survival * 100)
    
    
    defatultModel = getDefaultModels(valuationDate, len(loanData), hazardRate = hazardRate, correlation = correlation)
    
    for scenario in scenarios:
        print "\nRate Scenario " + str(scenario) + "(bps) Simualtion starts: " + str(datetime.datetime.now())
        # Build default model
        defatultModel.reset()
        print "Default model is ready..." + str(datetime.datetime.now())
        # Get loans pool
        loansPool = buildLoansPool(loanData, scenario)
        print "loans pool is ready..." + str(datetime.datetime.now())
        
        # Initialize cash flow generator
        flowGenerator = ColletralFlowGenerator(loansPool, survival)
        print "Cash flow generator is ready..." + str(datetime.datetime.now())

        for simulate in xrange(simulations):
            dpVec = defatultModel.nextProbalilitySequence()
            dDatesVec = defatultModel.determineDefaultTime(dpVec, 5.0)
            (coupCF, prinCF) = flowGenerator.simulatingOnePath(dDatesVec)
            
            # Cash flow report by frequency (e.g. monthly, quarterly, weekly
            principleByFrequency = aggregateCashFlowByFrequency(prinCF, Monthly)
            interestByFrequency = aggregateCashFlowByFrequency(coupCF, Monthly)
            cashFlowDF = colletralCashFlowsToDF(principleByFrequency, interestByFrequency)
            
            if simulate == 0:
                cashFlowDFSimulateSum = cashFlowDF
            else:
                cashFlowDFSimulateSum = cashFlowDFSimulateSum + cashFlowDF
                
        cashFlowDFSimulateSum = cashFlowDFSimulateSum / simulations    
        cashFlowDFSimulateSum.to_excel(writer, str(scenario))
        
        print "Rate Scenario " + str(scenario) + "(bps) Simualtion ends: " + str(datetime.datetime.now())
        
        
    writer.save()