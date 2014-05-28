# -*- coding: utf-8 -*-

'''
Created on 2014-4-28

@author: cheng.li
'''

import pandas as pd
import datetime as dt
from CAL.PyCAL import *
import CAL

def changex(x):
    try:
        return int(x)
    except:
        return x
    
def stringToDate(x):
    try:
        return pd.Timestamp(str(x))
    except:
        return x

def fillEmptyFreq(x):
    if x == 1 or x == 2:
        return x
    else:
        return 0
    
def totalMonthToPeriod(x):
    tmp = x / 12
    if tmp > 0:
        return str(tmp) + 'Y'
    else:
        return str(x) + 'M'

if __name__ == '__main__':
    treasuryDF = pd.read_excel(u'国债报价.xls', 'Sheet1')
    treasuryInfo = pd.read_excel(u'国债数据.xls', 'Sheet1')
    
    # Prepare the clean data
    # 1. Only include the bonds who have fixed coupon;
    # 2. Cast the ticker;
    # 3. Change date string to python date object
    treasuryDF = treasuryDF[['OFFC_CODE2', 'Time', 'COUPN_RATE', 'PAY_FREQ', 'YIELD', 'MATUR_DATE']]
    treasuryInfo = treasuryInfo[['BOND_NAME', 'TICKER_SYMBOL', 'FIRST_ACCRUAL_DT', 'ISSUE_PRICE', 'ISSUE_DT', 'EXCHANGE_LISTED_DT','COUPON_TYPE_CD', 'MATURITY_DT']]
    treasuryInfo = treasuryInfo[treasuryInfo["COUPON_TYPE_CD"] != 'FLOAT']
    treasuryInfo.dropna(subset = ['EXCHANGE_LISTED_DT'], inplace = True)
    
    treasuryInfo['TICKER_SYMBOL'] = treasuryInfo['TICKER_SYMBOL'].apply(changex)
    treasuryDF['MATUR_DATE'] = treasuryDF['MATUR_DATE'].apply(stringToDate)
    
    # Attache tenor info to treasury info data frame
    treasuryInfo['YEAR'] = treasuryInfo['MATURITY_DT'].apply(lambda x: x.year) - treasuryInfo['FIRST_ACCRUAL_DT'].apply(lambda x: x.year) 
    treasuryInfo['MONTH'] = treasuryInfo['MATURITY_DT'].apply(lambda x: x.month) - treasuryInfo['FIRST_ACCRUAL_DT'].apply(lambda x: x.month) 
    treasuryInfo['TOTAL_MONTH'] = treasuryInfo['YEAR'] * 12 + treasuryInfo['MONTH']
    
    treasuryInfo['TENOR'] = treasuryInfo['TOTAL_MONTH'].apply(totalMonthToPeriod)
    treasuryInfo = treasuryInfo[['BOND_NAME', 'TICKER_SYMBOL', 'FIRST_ACCRUAL_DT', 'ISSUE_PRICE', 'ISSUE_DT', 'EXCHANGE_LISTED_DT','COUPON_TYPE_CD', 'MATURITY_DT',
                             'TENOR']]
    
    # Get the OTR(on-the-run) bonds info (time series data)
    timeRange = pd.date_range('20100101', '20140520')
    otrDF = pd.DataFrame(index = timeRange)
    pivot = treasuryInfo.groupby('TENOR').count()
    for name in pivot.index:
        otrDF[name] = None
    
    for name in otrDF.columns:
        otrDF['O' + name] = None
        otrDF['OO' + name] = None
        tmpDF = treasuryInfo[treasuryInfo['TENOR'] == name].sort('EXCHANGE_LISTED_DT')
        dateIndex = otrDF.index
        exchangeDate = tmpDF['EXCHANGE_LISTED_DT']
        maturityDate = tmpDF['MATURITY_DT']
        bondName = tmpDF['TICKER_SYMBOL']
        #bondName = tmpDF['BOND_NAME']
        startRow = 0
        
        treasuryInfoIndex = tmpDF.index
        columnRes = pd.Series(index = dateIndex)
        columnRes2 = pd.Series(index = dateIndex)
        columnRes3 = pd.Series(index = dateIndex)
        pIndex = None
        for index in dateIndex:
            try:
                while (exchangeDate[treasuryInfoIndex[startRow]]>index or exchangeDate[treasuryInfoIndex[startRow+1]]<index) and startRow < (len(treasuryInfoIndex)-1):
                    startRow = startRow + 1
            except:
                pass
            if maturityDate[treasuryInfoIndex[startRow]] >= index: 
                try:
                    tmp = columnRes[index-1]
                except:
                    tmp = None
                columnRes[index] = bondName[treasuryInfoIndex[startRow]]
                if tmp != columnRes[index]:
                    try:
                        columnRes2[index] = columnRes[pIndex]
                    except:
                        pass
                    try:
                        columnRes3[index] = columnRes2[pIndex]
                    except:
                        pass
                else:
                    try:
                        columnRes2[index] = columnRes2[pIndex]
                    except:
                        pass
                    try:
                        columnRes3[index] = columnRes3[pIndex]
                    except:
                        pass
            pIndex = index
        otrDF[name] = columnRes
        otrDF['O' + name] = columnRes2
        otrDF['OO' +name] = columnRes3
    otrDF.fillna('None', inplace = True)
    
    otrDF = otrDF.reindex(columns = ['2M', 'O2M', 'OO2M', '3M', 'O3M', 'OO3M', '6M', 'O6M', 'OO6M',
                         '9M', 'O9M', 'OO9M', '1Y', 'O1Y', 'OO1Y', '2Y', 'O2Y', 'OO2Y',
                         '3Y', 'O3Y', 'OO3Y', '5Y', 'O5Y', 'OO5Y', '7Y', 'O7Y', 'OO7Y',
                         '10Y', 'O10Y', 'OO10Y', '15Y', 'O15Y', 'OO15Y', '20Y', 'O20Y', 'OO20Y',
                         '30Y', 'O30Y', 'OO30Y', '50Y', 'O50Y', 'OO50Y'])
    #otrDF.to_excel(u'OTR序列.xls')
    
    # Get the yield time series for OTR bonds
    treasuryDF['quoteDate'] = treasuryDF['Time'].apply(lambda x:x.date())
    
    dfDict = {}
    dfDict['OTR'] = {}
    dfDict['OOTR'] = {}
    dfDict['OOOTR'] = {}
    
    tenorNames = [r'1Y', r'2Y', r'3Y', r'5Y', r'7Y', r'10Y']
    
    for name in tenorNames:
        tmpDF = otrDF[[name, 'O' + name, 'OO' + name]]
        res = [pd.Timestamp(x).date() for x in tmpDF.index.values]
        tmpDF['Date'] = res
            
        res1= pd.merge(tmpDF[[name, 'Date']], treasuryDF, how = 'inner', left_on = [name, 'Date'], right_on = ['OFFC_CODE2', 'quoteDate'])            
        res2= pd.merge(tmpDF[['O' + name, 'Date']], treasuryDF, how = 'inner', left_on = ['O' + name, 'Date'], right_on = ['OFFC_CODE2', 'quoteDate'])
        res3= pd.merge(tmpDF[['OO'+ name, 'Date']], treasuryDF, how = 'inner', left_on = ['OO' + name, 'Date'], right_on = ['OFFC_CODE2', 'quoteDate'])
        
        dfDict['OTR'][name] = res1
        dfDict['OOTR'][name] = res2
        dfDict['OOOTR'][name] = res3
        
    # Let's do some calculation on On-the-Run bonds
    for group, groupDF in dfDict.items():
        for name, df in groupDF.items():
            averageDF = df[['OFFC_CODE2','COUPN_RATE', 'PAY_FREQ', 'MATUR_DATE', 'YIELD', 'Date']].groupby('Date').mean()
            endMaturity = df[['MATUR_DATE', 'Date']].groupby('Date').last()
            averageDF['TENOR'] = name
            averageDF['MATUR_DATE'] = endMaturity['MATUR_DATE']
            dfDict[group][name] = averageDF
        
    calendar = Calendar('China.IB')
    bizDates = BizDatesList(calendar, '20131216', '20140520')
    
    curveCandidateInstrument = []
    
    for date in bizDates:
        dtDate = date.date()
        
        for name in tenorNames:
            try:
                tmpDF = dfDict['OTR'][name]
                match = tmpDF.ix[dtDate]
                candidate = {'date':dtDate, 'code':match['OFFC_CODE2'], 'tenor':name, 'coupon':match['COUPN_RATE'], 'freq':match['PAY_FREQ'], 
                             'maturity':match['MATUR_DATE'], 'yield':match['YIELD'], 'alias':name}
                curveCandidateInstrument.append(candidate)
                #continue
            except:
                pass
            
            try:
                tmpDF = dfDict['OOTR'][name]
                match = tmpDF.ix[dtDate]
                candidate = {'date':dtDate, 'code':match['OFFC_CODE2'], 'tenor':name, 'coupon':match['COUPN_RATE'], 'freq':match['PAY_FREQ'], 
                             'maturity':match['MATUR_DATE'], 'yield':match['YIELD'], 'alias':'O'+name}
                curveCandidateInstrument.append(candidate)
                #continue
            except:
                pass
            
            try:
                tmpDF = dfDict['OOOTR'][name]
                match = tmpDF.ix[dtDate]
                candidate = {'date':dtDate, 'code':match['OFFC_CODE2'], 'tenor':name, 'coupon':match['COUPN_RATE'], 'freq':match['PAY_FREQ'], 
                             'maturity':match['MATUR_DATE'], 'yield':match['YIELD'], 'alias':'OO'+name}
                curveCandidateInstrument.append(candidate)
                #continue
            except Exception:
                pass
            
    curveInstruments = pd.DataFrame(curveCandidateInstrument)
    curveInstruments.sort(['date','maturity'], inplace = True)
    curveInstruments.dropna(inplace=True)
    curveInstruments.to_excel(u'基准债券.xls')
    #print tmpDF
    #print match        
    #print candidate
    
    