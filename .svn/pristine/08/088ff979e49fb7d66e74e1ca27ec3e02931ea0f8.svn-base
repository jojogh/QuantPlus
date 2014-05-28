'''
Created on 2013-12-26

@author: cheng.li
'''


import CAL
import pprint

def calcuatingBondAnalytics(settlementDate, 
                            startDate, 
                            maturity, 
                            period, 
                            coupons,
                            benchmarkYield = 0.03,
                            repeat = 1):
    
    yieldDayCounter = CAL.Actual365NoLeap()
    compoundingMethod = CAL.Compounded
    frequency = CAL.Annual
    
    # Do the unnecessary repeating to test on performance
    for i in xrange(repeat):
        myBond = CAL.CTBFixedBond(issueDate = startDate,
                                  settlementDays = 1,
                                  faceAmount = 100.0,
                                  startDate= startDate,
                                  maturity = maturity,
                                  tenor = period,
                                  coupons = coupons)
    

        # Bond analytics
        cleanPrice = myBond.cleanPrice(benchmarkYield, yieldDayCounter, compoundingMethod, frequency,  settlementDate)
        accruedAmount = myBond.accruedAmount(settlementDate)
        conversionFactor1403 = myBond.conversionFactor(2014,CAL.March)
        conversionFactor1406 = myBond.conversionFactor(2014,CAL.June)
        conversionFactor1409 = myBond.conversionFactor(2014,CAL.September)
        macaulayDuration = CAL.BondFunctions.duration(myBond, benchmarkYield, yieldDayCounter, compoundingMethod, frequency, CAL.Duration.Macaulay, settlementDate)
        modifiedDuration = CAL.BondFunctions.duration(myBond, benchmarkYield, yieldDayCounter, compoundingMethod, frequency, CAL.Duration.Modified, settlementDate)
        convexity = CAL.BondFunctions.convexity(myBond, benchmarkYield, yieldDayCounter, compoundingMethod, frequency, settlementDate)
        PV01 = - CAL.BondFunctions.basisPointValue(myBond, benchmarkYield, yieldDayCounter, compoundingMethod, frequency, settlementDate)

    return {"Benchmark Yield" : round(benchmarkYield, 4),
            "Clean Price" : round(cleanPrice,4),
            "Accrued Interest" : round(accruedAmount,4),
            "CF (TF1403)" : round(conversionFactor1403,4),
            "CF (TF1406)" : round(conversionFactor1406,4),
            "CF (TF1409)" : round(conversionFactor1409,4),
            "Macaulay Duration" : round(macaulayDuration,4),
            "Modified Duration" : round(modifiedDuration,4),
            "Convexity" : round(convexity,4),
            "PV01" : round(PV01,4)}

if __name__ == '__main__':
    
    # Benchmark bond 130020. Quote on Dec 25th, 2013. Settle on Dec 26, 2013
    settlementDate = CAL.Date(26, CAL.December, 2013)
    startDate = CAL.Date(17, CAL.October, 2013)
    maturity = CAL.Date(17, CAL.October, 2020)
    period = CAL.Period(1, CAL.Years)
    coupons = [0.0407]
    benchmarkYield = 0.047154
    repeat = 1000
    
    result = calcuatingBondAnalytics(settlementDate, startDate, maturity, period, coupons, benchmarkYield, repeat)
    
    pprint.pprint(result)