# -*- coding: utf-8 -*-
'''
Created on 2014-3-31

@author: cheng.li
'''

from CAL import *
import FunctionTools
import numpy as np

def __BuildZeroCurve__(dates, rates, dc, interp):
    if isinstance(dates[0], Date):
        if interp.upper() == 'LINEAR':
            return LinearZeroCurve(dates, rates, dc)
        elif interp.upper() == 'BACKWARDFLAT':
            return BackwardFlatZeroCurve(dates, rates, dc)
        elif interp.upper() == 'FORWARDFLAT':
            return ForwardFlatZeroCurve(dates, rates, dc)
        elif interp.upper() == 'CUBIC':
            return CubicZeroCurve(dates, rates, dc)
        elif interp.upper() == 'LOGLINEAR':
            return LogLinearZeroCurve(dates, rates, dc)
        else:
            raise Exception('#unknown interpolation type ' + str(interp) + ' method')
    else:
        if interp.upper() == 'LINEAR':
            return LinearZeroCurve(dates, rates, dc, NullCalendar(), Linear(), Continuous, Annual,True)
        elif interp.upper() == 'BACKWARDFLAT':
            return BackwardFlatZeroCurve(dates, rates, dc, NullCalendar(), BackwardFlat(), Continuous, Annual,True)
        elif interp.upper() == 'FORWARDFLAT':
            return ForwardFlatZeroCurve(dates, rates, dc, NullCalendar(), ForwardFlat(), Continuous, Annual,True)
        elif interp.upper() == 'CUBIC':
            return CubicZeroCurve(ddates, rates, dc, NullCalendar(), Cubic(), Continuous, Annual,True)
        elif interp.upper() == 'LOGLINEAR':
            return LogLinearZeroCurve(dates, rates, dc, NullCalendar(), LogLinear(), Continuous, Annual,True)
        else:
            raise Exception('#unknown interpolation type ' + str(interp) + ' method')

def __BuildDiscountCurve__(dates, rates, dc, interp):
    if interp.upper() == 'LINEAR':
        return LinearDiscountCurve(dates, rates, dc)
    elif interp.upper() == 'BACKWARDFLAT':
        return BackwardFlatDiscountCurve(dates, rates, dc)
    elif interp.upper() == 'FORWARDFLAT':
        return ForwardFlatDiscountCurve(dates, rates, dc)
    elif interp.upper() == 'CUBIC':
        return CubicDiscountCurve(dates, rates, dc)
    elif interp.upper() == 'LOGLINEAR':
        return LogLinearDiscountCurve(dates, rates, dc)
    else:
        raise Exception('#unknown interpolation type ' + str(interp) + ' method')

def __BuildForwardCurve__(dates, rates, dc, interp):
    if interp.upper() == 'LINEAR':
        return LinearForwardCurve(dates, rates, dc)
    elif interp.upper() == 'BACKWARDFLAT':
        return BackwardFlatForwardCurve(dates, rates, dc)
    elif interp.upper() == 'FORWARDFLAT':
        return ForwardFlatForwardCurve(dates, rates, dc)
    elif interp.upper() == 'CUBIC':
        return CubicForwardCurve(dates, rates, dc)
    elif interp.upper() == 'LOGLINEAR':
        return LogLinearForwardCurve(dates, rates, dc)
    else:
        raise Exception('#unknown interpolation type ' + str(interp) + ' method')

def YieldCurve(dates,
               rates,
               dayCounter = 0,
               trait = 'zero',
               interp = 'linear'):
    
    if not isinstance(dates[0], float):
        dates = map(FunctionTools.__parsePYDate__,dates)
    
    dates = list(dates)
    rates = list(rates)
    
    dc = FunctionTools.__parseDayCounter__(dayCounter)
    
    if trait.upper() == 'ZERO':
        return __BuildZeroCurve__(dates, rates, dc, interp)
    elif trait.upper() == 'DISCOUNT':
        return __BuildDiscountCurve__(dates, rates, dc, interp)
    elif trait.upper() == 'FORWARD':
        return __BuildForwardCurve__(dates, rates, dc, interp)
    else:
        raise Exception('#Unknown yield curve traits ' + str(trait) + ' type!')
    
def __ZeroYield__(yc, date, dayCounter = 0, comp = 2, freq = 1, extrapolate = True):
    date = FunctionTools.__parsePYDate__(date)
    dc = FunctionTools.__parseDayCounter__(dayCounter)
    comp = FunctionTools.__parseCompounding__(comp)
    freq = FunctionTools.__parseFrequency__(freq)
    return yc.zeroRate(date, dc, comp, freq, extrapolate).rate()

def ZeroYield(yc, date, dayCounter = 0, comp = 2, freq = 1, extrapolate = True):
    myFunc = np.frompyfunc(__ZeroYield__, 6, 1)
    rates = myFunc(yc, date, dayCounter, comp, freq, extrapolate) 
    return FunctionTools.__formatResult__(rates, ['zeroYield'])

def __DiscountFactor__(yc, date, extrapolate = True):
    date = FunctionTools.__parsePYDate__(date)
    return yc.discount(date, extrapolate)

def DiscountFactor(yc, date, extrapolate = True):
    myFunc = np.frompyfunc(__DiscountFactor__, 3, 1)
    df = myFunc(yc, date, extrapolate) 
    return FunctionTools.__formatResult__(df, ['discount'])

def __ForwardRate__(yc, startDate, endDate, dayCounter = 0, comp = 2, freq = 1, extrapolate = True):
    startDate = FunctionTools.__parsePYDate__(startDate)
    endDate = FunctionTools.__parsePYDate__(endDate)
    dc = FunctionTools.__parseDayCounter__(dayCounter)
    comp = FunctionTools.__parseCompounding__(comp)
    freq = FunctionTools.__parseFrequency__(freq)
    return yc.forwardRate(startDate, endDate, dc, comp, freq, extrapolate).rate()

def ForwardRate(yc, startDate, endDate, dayCounter = 0, comp = 2, freq = 1, extrapolate = True):
    myFunc = np.frompyfunc(__ForwardRate__, 7, 1)
    rates = myFunc(yc, startDate, endDate, dayCounter, comp, freq, extrapolate) 
    return FunctionTools.__formatResult__(rates, ['forwardRate'])

if __name__ == '__main__':
    import pandas as pd
    from DataAPI import Plot

    dates = [pd.Timestamp('20131001'), pd.Timestamp('20140101'), pd.Timestamp('20140401'), 
             pd.Timestamp('20140701'), pd.Timestamp('20141001')]
    rates = np.linspace(0.02, 0.08, 5)
    
    dates = [0.0, 10.2, 10.3, 10.4, 10.5]
    rates = [0.15, 0.2, 0.25, 0.25, 0.35]
    
    yc = LinearZeroCurve(dates, rates, Actual360(), NullCalendar(), Linear(), Continuous, Annual, True)
    yc = YieldCurve(dates, rates, dayCounter = 0, trait = 'zero', interp = 'Linear')
    
    res =  ZeroYield(yc, pd.DateRange('20141212', '20200202'))
    res['years'] = np.linspace(0,50, len(pd.DateRange('20141212', '20200202')))
    
    Plot(res, settings = {'x':'years'})
    #print DiscountFactor(yc, dates)
    #print ForwardRate(yc, pd.Timestamp('20131001'), dates)