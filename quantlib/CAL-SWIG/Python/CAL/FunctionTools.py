# -*- coding: utf-8 -*-
'''
Created on 2014-3-18

@author: cheng.li
'''

from CAL import *
import pandas as pd
import datetime as dt

def SetEvaluationDate(date):
    try:
        calDate = __parsePYDate__(date)
        Settings.instance().setEvaluationDate(calDate)
        return True
    except:
        return False
def EvaluationDate():
    return Settings.instance().evaluationDate()

def __parsePYDate__(datePY):
    datePY = pd.Timestamp(datePY)
    year = datePY.year
    month = datePY.month
    day = datePY.day
    return Date(day, month, year)

def __parseCALDate__(calDate):
    return pd.Timestamp(dt.datetime(calDate.year(), calDate.month(), calDate.dayOfMonth()))

def __parseInerp__(interp):
    if interp.upper() == 'LINEAR':
        return Linear()
    elif interp.upper() == 'BACKWARDFLAT':
        return BackwardFlat();
    elif interp.upper() == 'FORWARDFLAT':
        return ForwardFlat()
    elif interp.upper() == 'CUBIC':
        return Cubic()
    elif interp.upper() == 'LOGLINEAR':
        return LogLinear()
    else:
        raise Exception('#unknown interpolation type ' + str(interp) + ' method')

def __parseDate__(dateInteger):
    year = dateInteger / 10000
    dateInteger = dateInteger - year * 10000
    month = dateInteger / 100
    day = dateInteger - month * 100
    return Date(day, month, year)

def __parseCompounding__(comInteger):
    if comInteger == 0:
        return Compounded
    elif comInteger == 1:
        return Simple
    elif comInteger == 2:
        return Continuous
    else:
        raise Exception("#unknown compounding " + str(comInteger) + " method")
    

def __parseTenor__(tenorString):
    tenor = int(tenorString)
    return Period(tenor, Years)

def __parseFrequency__(freqString):
    if freqString == 1:
        return Annual
    elif freqString == 2:
        return Semiannual
    elif freqString == 4:
        return Quarterly
    elif freqString == 12:
        return Monthly
    else:
        raise Exception("#unknown frequency " + str(freqString) + " parsed!") 
    
def __parseDayCounter__(dcString):
    if dcString == 0:
        return Actual365Fixed()
    elif dcString == 1:
        return Actual365NoLeap()
    elif dcString == 2:
        return ActualActual(ActualActual.ISMA)
    elif dcString == 3:
        return Actual360()
    elif dcString == 4:
        return ActualActualNoLeap()
    else:
        raise Exception("#unknown day counter " + str(dcString) + " parsed")
    
def __formatResult__(rawResult, columnNames):
    
    if not isinstance(rawResult,tuple):
        rawResult = (rawResult,)
    
    if isinstance(rawResult[0], pd.DataFrame):
        for i, name in enumerate(columnNames):
            rawResult[i].rename(columns={rawResult[i].columns[0]:name}, inplace=True)
        
        if len(columnNames) == 1:
            bigDataFrame = rawResult[0]
        else:
            bigDataFrame = pd.merge(rawResult[0],rawResult[1], left_index=True, right_index=True, suffixes=['_left', '_right'])
        for i in xrange(2, len(columnNames)):
            bigDataFrame = pd.merge(bigDataFrame,rawResult[i], left_index=True, right_index=True, suffixes=['_left', '_right'])
        bigDataFrame.columns = columnNames
        return bigDataFrame
    elif isinstance(rawResult[0], pd.Series):
        myDict = {}
        for i, name in enumerate(columnNames):
            myDict[name] = rawResult[i]
        bigDataFrame = pd.DataFrame(myDict)
        bigDataFrame = bigDataFrame.reindex_axis(columnNames,axis=1)
        return bigDataFrame
    else:
        length = 0
        try:
            length = len(rawResult[0])
        except:
            length = 1
        index = range(1,length + 1)
        myDict = {}
        for i, name in enumerate(columnNames):
            myDict[name] = rawResult[i]
        bigDataFrame = pd.DataFrame(myDict, index= index)
        bigDataFrame = bigDataFrame.reindex_axis(columnNames, axis=1)
        
        return bigDataFrame
    
if __name__ == '__main__':
    pass