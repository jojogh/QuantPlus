# -*- coding: utf-8 -*-
'''
Created on 2014-3-18

@author: cheng.li
'''
from CAL import *
import FunctionTools
import numpy as np
import pandas as pd
import datetime as dt

def __CTBZeroBondEval__(evaluationDate, 
                    issueDate,
                    issuePrice,
                    maturityDate,
                    ytm,
                    DayCounter = 2,
                    settlementDays = 0):
    evaluationDate = FunctionTools.__parsePYDate__(evaluationDate)
    settlementCalendar = China(China.IB)
    settlementDate = settlementCalendar.advance(evaluationDate, settlementDays, Days)
    issueDate = FunctionTools.__parsePYDate__(issueDate)
    dc = FunctionTools.__parseDayCounter__(DayCounter)
    maturityDate = FunctionTools.__parsePYDate__(maturityDate)
    
    bond = CTBZeroBond(settlementDays,
                       NullCalendar(),
                       100.0,
                       issuePrice,
                       issueDate,
                       dc,
                       maturityDate)
    
    comp = Simple
    frequency = Annual
    
    cleanPrice = bond.cleanPrice(ytm, dc, comp, frequency, settlementDate)
    accrue = bond.accruedAmount(settlementDate)
    dirtyPrice = bond.dirtyPrice(ytm, dc, comp, frequency, settlementDate)
    modifiedDuratin = BondFunctions.duration(bond, ytm, dc, comp, frequency, Duration.Modified, settlementDate)
    convexity = BondFunctions.convexity(bond, ytm, dc, comp, frequency, settlementDate)
    return cleanPrice, accrue, dirtyPrice, modifiedDuratin, convexity

def __CTBZeroBondYield__(evaluationDate, 
                    issueDate,
                    issuePrice,
                    maturityDate,
                    cleanPrice,
                    DayCounter = 2,
                    settlementDays = 0):
    evaluationDate = FunctionTools.__parsePYDate__(evaluationDate)
    settlementCalendar = China(China.IB)
    settlementDate = settlementCalendar.advance(evaluationDate, settlementDays, Days)
    issueDate = FunctionTools.__parsePYDate__(issueDate)
    dc = FunctionTools.__parseDayCounter__(DayCounter)
    maturityDate = FunctionTools.__parsePYDate__(maturityDate)
    
    bond = CTBZeroBond(settlementDays,
                       NullCalendar(),
                       100.0,
                       issuePrice,
                       issueDate,
                       dc,
                       maturityDate)
    
    comp = Simple
    frequency = Annual
    
    ytm = bond.bondYield(cleanPrice, dc, comp, frequency, settlementDate)
    accrue = bond.accruedAmount(settlementDate)
    dirtyPrice = bond.dirtyPrice(ytm, dc, comp, frequency, settlementDate)
    modifiedDuratin = BondFunctions.duration(bond, ytm, dc, comp, frequency, Duration.Modified, settlementDate)
    convexity = BondFunctions.convexity(bond, ytm, dc, comp, frequency, settlementDate)
    return ytm, accrue, dirtyPrice, modifiedDuratin, convexity

def CTBZeroBondYield(evaluationDate, 
                    issueDate,
                    issuePrice,
                    maturityDate,
                    cleanPrice,
                    DayCounter = 2,
                    settlementDays = 0):
    '''
    固定利率债券
    Input：
    evaluationDate -- 估值日
    issueDate      -- 债券发行日
    issuePrice     -- 发行价格
    maturityDate   -- 到期日
    cleanPrice     -- 净价
    DayCounter     -- 计息方法，0：Actual/365 (fixed)，1：Actual/365 (No Leap)，2：Actual/Actual (ISMA)，3：Actual/360. 4: Actual/Actual (No Leap)
    settlementDays -- 清算速度
    
    Output:
    (yield, accruedInterest, dirtyPrice, modifiedDuratin, convexity)
    '''
    
    myFunc = np.frompyfunc(__CTBZeroBondYield__, 7, 5)
    bondPrice = myFunc(evaluationDate, 
                    issueDate,
                    issuePrice,
                    maturityDate,
                    cleanPrice,
                    DayCounter,
                    settlementDays)
    
    return FunctionTools.__formatResult__(bondPrice, ['yield', 'accruedAmount', 'dirtyPrice', 'modifiedDuration', 'convexity'])

def CTBZeroBondEval(evaluationDate, 
                    issueDate,
                    issuePrice,
                    maturityDate,
                    ytm,
                    DayCounter = 2,
                    settlementDays = 0):
    '''
    固定利率债券
    Input：
    evaluationDate -- 估值日
    issueDate      -- 债券发行日
    issuePrice     -- 发行价格
    maturityDate   -- 到期日
    ytm            -- 到期收益率
    DayCounter     -- 计息方法，0：Actual/365 (fixed)，1：Actual/365 (No Leap)，2：Actual/Actual (ISMA)，3：Actual/360. 4: Actual/Actual (No Leap)
    settlementDays -- 清算速度
    
    Output:
    (cleanPrice, accruedInterest, dirtyPrice, modifiedDuratin, convexity)
    '''
    
    myFunc = np.frompyfunc(__CTBZeroBondEval__, 7, 5)
    bondPrice = myFunc(evaluationDate, 
                    issueDate,
                    issuePrice,
                    maturityDate,
                    ytm,
                    DayCounter,
                    settlementDays)
    
    return FunctionTools.__formatResult__(bondPrice, ['cleanPrice', 'accruedAmount', 'dirtyPrice', 'modifiedDuration', 'convexity'])

def __FixedRateBondEval__(evaluationDate,
                      startDate,
                      tenor,
                      coupon,
                      ytm,
                      compounding,
                      frequency = 1,
                      DayCounter = 2,
                      settlementDays = 0):
    evaluationDate = FunctionTools.__parsePYDate__(evaluationDate)
    settlementCalendar = China(China.IB)
    settlementDate = settlementCalendar.advance(evaluationDate, settlementDays, Days)
    startDate = FunctionTools.__parsePYDate__(startDate)
    tenor = FunctionTools.__parseTenor__(tenor)
    endDate = startDate + tenor
    frequency = FunctionTools.__parseFrequency__(frequency)
    couponPeriod = Period(frequency)
    dc = FunctionTools.__parseDayCounter__(DayCounter)
    comp = FunctionTools.__parseCompounding__(compounding)
    
    schedule = Schedule(startDate,
                            endDate,
                            couponPeriod,
                            NullCalendar(),
                            Unadjusted,
                            Unadjusted,
                            DateGeneration.Backward,
                            False,
                            )
    
    bond = FixedRateBond(settlementDays,
                         100.0,
                         schedule,
                         [coupon],
                         dc,
                         Unadjusted,
                         100.0)
    
    cleanPrice = bond.cleanPrice(ytm, dc, comp, frequency, settlementDate)
    accrue = bond.accruedAmount(settlementDate)
    dirtyPrice = bond.dirtyPrice(ytm, dc, comp, frequency, settlementDate)
    macaulyDuration = BondFunctions.duration(bond, ytm, dc, comp, frequency, Duration.Macaulay, settlementDate)
    modifiedDuratin = BondFunctions.duration(bond, ytm, dc, comp, frequency, Duration.Modified, settlementDate)
    convexity = BondFunctions.convexity(bond, ytm, dc, comp, frequency, settlementDate)
    return cleanPrice, accrue, dirtyPrice, macaulyDuration, modifiedDuratin, convexity

def __FixedRateBondYield__(evaluationDate,
                      startDate,
                      tenor,
                      coupon,
                      cleanPrice,
                      compounding,
                      frequency = 1,
                      DayCounter = 2,
                      settlementDays = 0):
    evaluationDate = FunctionTools.__parsePYDate__(evaluationDate)
    settlementCalendar = China(China.IB)
    settlementDate = settlementCalendar.advance(evaluationDate, settlementDays, Days)
    startDate = FunctionTools.__parsePYDate__(startDate)
    tenor = FunctionTools.__parseTenor__(tenor)
    endDate = startDate + tenor
    frequency = FunctionTools.__parseFrequency__(frequency)
    couponPeriod = Period(frequency)
    dc = FunctionTools.__parseDayCounter__(DayCounter)
    comp = FunctionTools.__parseCompounding__(compounding)
    
    schedule = Schedule(startDate,
                            endDate,
                            couponPeriod,
                            NullCalendar(),
                            Unadjusted,
                            Unadjusted,
                            DateGeneration.Backward,
                            False,
                            )
    
    bond = FixedRateBond(settlementDays,
                         100.0,
                         schedule,
                         [coupon],
                         dc,
                         Unadjusted,
                         100.0)
    
    ytm = bond.bondYield(cleanPrice, dc, comp, frequency, settlementDate)
    accrue = bond.accruedAmount(settlementDate)
    dirtyPrice = bond.dirtyPrice(ytm, dc, comp, frequency, settlementDate)
    macaulyDuration = BondFunctions.duration(bond, ytm, dc, comp, frequency, Duration.Macaulay, settlementDate)
    modifiedDuratin = BondFunctions.duration(bond, ytm, dc, comp, frequency, Duration.Modified, settlementDate)
    convexity = BondFunctions.convexity(bond, ytm, dc, comp, frequency, settlementDate)
    return ytm, accrue, dirtyPrice, macaulyDuration, modifiedDuratin, convexity 

def FixedRateBondYield(evaluationDate,
                      startDate,
                      tenor,
                      coupon,
                      cleanPrice,
                      compounding,
                      frequency = 1,
                      DayCounter = 2,
                      settlementDays = 0):
    '''
    固定利率债券
    Input：
    evaluationDate -- 估值日
    startDate      -- 债券起息日
    tenor          -- 期限，单位年
    coupon         -- 票息
    cleanPrice     -- 净价
    compounding    -- 复利方法，0：复利，1：简单利率
    frequency      -- 付息周期，1：每年，2：每半年，4：每季度，12：每月
    DayCounter     -- 计息方法，0：Actual/365 (fixed)，1：Actual/365 (No Leap)，2：Actual/Actual (ISMA)，3：Actual/360. 4: Actual/Actual (No Leap)
    settlementDays -- 清算速度
    
    Output:
    (yield, accruedInterest, dirtyPrice, macaulyDuration， modifiedDuratin, convexity)
    '''
    
    myFunc = np.frompyfunc(__FixedRateBondYield__, 9, 6)
    bondPrice = myFunc(evaluationDate,
                      startDate,
                      tenor,
                      coupon,
                      cleanPrice,
                      compounding,
                      frequency,
                      DayCounter,
                      settlementDays)
    
    return FunctionTools.__formatResult__(bondPrice, ['yield', 'accruedAmount', 'dirtyPrice', 'macaulyDuration', 'modifiedDuration', 'convexity'])
    

def FixedRateBondEval(evaluationDate,
                      startDate,
                      tenor,
                      coupon,
                      ytm,
                      compounding,
                      frequency = 1,
                      DayCounter = 2,
                      settlementDays = 0):
    '''
    固定利率债券
    Input：
    evaluationDate -- 估值日
    startDate      -- 债券起息日
    tenor          -- 期限，单位年
    coupon         -- 票息
    ytm            -- 到期收益率
    compounding    -- 复利方法，0：复利，1：简单利率
    frequency      -- 付息周期，1：每年，2：每半年，4：每季度，12：每月
    DayCounter     -- 计息方法，0：Actual/365 (fixed)，1：Actual/365 (No Leap)，2：Actual/Actual (ISMA)，3：Actual/360. 4: Actual/Actual (No Leap)
    settlementDays -- 清算速度
    
    Output:
    (cleanPrice, accruedInterest, dirtyPrice, macaulyDuration， modifiedDuratin, convexity)
    '''
    
    myFunc = np.frompyfunc(__FixedRateBondEval__, 9, 6)
    bondPrice = myFunc(evaluationDate,
                      startDate,
                      tenor,
                      coupon,
                      ytm,
                      compounding,
                      frequency,
                      DayCounter,
                      settlementDays)
    
    return FunctionTools.__formatResult__(bondPrice, ['cleanPrice', 'accruedAmount', 'dirtyPrice', 'macaulyDuration', 'modifiedDuration', 'convexity'])

if __name__ == '__main__':
    
    evaluationDate = pd.DataFrame([pd.Timestamp('20140101')]*4)
    startDate = dt.datetime(2013,12,2)
    
    coupon = pd.DataFrame({'coupon':[0.05,0.05]})
    res = FixedRateBondEval(evaluationDate, startDate, 2, 0.05, 0.05, 0, 12, 1)
    print res
    pass