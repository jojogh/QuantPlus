# -*- coding: utf-8 -*-
'''
Created on 2014-4-4

@author: cheng.li
'''

from CAL import *
from FunctionTools import __parsePYDate__, __parseCALDate__
from Config import __holidayCenterStrs__, __holidayCenterCodes__
import pandas as pd

def Calendar(holCenter):
    '''
    Input:
    holCenter -- 字符串或代码，例如：'China.SSE'或者10
    
    output:
    calendar对象
    '''
    if isinstance(holCenter, str):
        holCenter= holCenter.upper()
        if __holidayCenterStrs__.has_key(holCenter):
            holi = __holidayCenterStrs__[holCenter]
            return holi[0](holi[1])
        else:
            raise Exception('#' + holCenter + ' cant be recognized as valid holiday center')
    elif isinstance(holCenter, int):
        if __holidayCenterCodes__.has_key(holCenter):
            holi = __holidayCenterCodes__[holCenter]
            return holi[0](holi[1])
        else:
            raise Exception('#' + str(holCenter) + ' cant be recognized as valid holiday center')
    else:
        raise Exception('#' + str(holCenter) + ' parameter cant be recognized as valid type')
    
def BizDatesList(cal, startDate, endDate):
    '''
    Input:
    cal       -- calendar对象
    startDate -- 参考时间段起始
    enDate    -- 参考时间段结束
    
    Output:
    工作日列表
    '''
    totalDateRange = pd.date_range(startDate, endDate)   
    bizDates = []
    
    for sampleDate in totalDateRange[:-1]:
        calDate = __parsePYDate__(sampleDate)
        if cal.isBusinessDay(calDate):
            bizDates.append(sampleDate)   
    return bizDates

def HolDatesList(cal, startDate, endDate):
    '''
    Input:
    cal       -- calendar对象
    startDate -- 参考时间段起始
    enDate    -- 参考时间段结束
    
    Output:
    节假日列表
    '''
    totalDateRange = pd.date_range(startDate, endDate)   
    holDates = []    
    for sampleDate in totalDateRange[:-1]:
        calDate = __parsePYDate__(sampleDate)
        if not cal.isBusinessDay(calDate):
            holDates.append(sampleDate)   
    return holDates

def AddHoliday(cal, newHolDate):
    '''
    Input:
    cal        -- calendar对象
    newHolDate -- 新节假日
    
    Output:
    新的calendar对象
    '''
    newHolDate = pd.Timestamp(newHolDate)
    calDate = __parsePYDate__(newHolDate)
    cal.addHoliday(calDate)
    return cal

def RemoveHoliday(cal, targetHolDate):
    '''
    Input:
    cal        -- calendar对象
    targetHolDate -- 旧节假日
    
    Output:
    新的calendar对象
    '''
    targetHolDate = pd.Timestamp(targetHolDate)
    calDate = __parsePYDate__(targetHolDate)
    cal.removeHoliday(calDate)
    return cal

def IsBizDay(cal, testDate):
    testDate = pd.Timestamp(testDate)
    calDate = __parsePYDate__(testDate)
    return cal.isBusinessDay(calDate)

def IsHoliday(cal, testDate):
    testDate = pd.Timestamp(testDate)
    calDate = __parsePYDate__(testDate)
    return cal.isHoliday(calDate)

def IsMonthEnd(cal, testDate):
    testDate = pd.Timestamp(testDate)
    calDate = __parsePYDate__(testDate)
    return cal.isEndOfMonth(calDate)

def AdvanceDate(cal, todayDate, period, convention, endOfMonth = False):
    periodObj = PeriodParser.parse(period)
    todayDate = pd.Timestamp(todayDate)
    calDate = __parsePYDate__(todayDate)
    res = cal.advance(calDate, periodObj.length(), periodObj.units(), convention, endOfMonth)
    return __parseCALDate__(res)
    
if __name__ == '__main__':

   myCalendar = Calendar(11)
   print myCalendar.name()
   print BizDatesList(myCalendar, pd.Timestamp('20130101'), pd.Timestamp('20141231'))
   print HolDatesList(myCalendar, pd.Timestamp('20130101'), pd.Timestamp('20141231'))
   print IsBizDay(myCalendar, '20141231')
   print IsHoliday(myCalendar, '20141231')
   print IsMonthEnd(myCalendar, '20141231')
   print AdvanceDate(myCalendar, '20131231', '2d', Following)
   print AdvanceDate(myCalendar, '20131231', '2b', Following)
   print IsBizDay(myCalendar, '20150101')