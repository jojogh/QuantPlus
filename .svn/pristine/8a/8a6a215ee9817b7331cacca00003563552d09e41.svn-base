# -*- coding: utf-8 -*-
'''
Created on 2014-3-17

@author: cheng.li
'''
import pandas as pd
import numpy as np
import matplotlib
from matplotlib import pylab
from matplotlib.font_manager import FontProperties
import platform
import httplib
import StringIO
import Config
from pylab import *
from DBConnection import BondDBUtilities
    

encoding = 'gb2312'

def __getCSV__(requestString, httpClient):
    try:
        httpClient.request('GET', requestString)
        response = httpClient.getresponse()
        return response.read()
    finally:
        httpClient.close()

def __getConn__():
    domain = Config.__server_config__[Config.__server__]['host']
    port = Config.__server_config__[Config.__server__]['port']
    return httplib.HTTPConnection(domain, port)
    
def MarketDataGetHistDailyQuotes(securityID, fields, startDate, endDate):
    '''
    
    获取历史日线数据API
    输入：
    securityID -- 证券代码
    fields -- 数据项，可以是一个列表
    startDate -- 数据获取开始日，为YYYYMMDD字符串
    endDate -- 数据获取截止日期，为YYYYMMDD字符串
    
    输出：
    pandas DataFrame格式二维列表
    
    '''
    
    httpClient = __getConn__()
    
    functionName = 'MarketDataGetHistDailyQuotes'
    
    requestString = Config.__function_config__[functionName][Config.__server__]['api']
    requestString += "securityID=" + securityID
    requestString += "&field="
    if hasattr(fields, '__iter__'):
        if fields != None:
            for field in fields:
                requestString += field + ","
            requestString = requestString[:-1]
    else:
        if fields != None:
            requestString += fields
    requestString += "&startDate=" +startDate
    requestString += "&endDate=" +endDate
    
    csvString = __getCSV__(requestString, httpClient)
    
    try:
        myIO = StringIO.StringIO(csvString)
        pdFrame = pd.read_csv(myIO, encoding= encoding, parse_dates = [0], dtype = {'ticker':'str'})
        if not pdFrame.empty:
            pdFrame.index.name = 'index'
            return pdFrame
    finally:
        myIO.close()
                    
    # try to read as bonds
    return BondDBUtilities.HistBondPrice(securityID, startDate, endDate, fields)


def MarketDataGetHistTicks(securityID, specificDate, fields = None):
    '''
    
    获取历史tick数据API
    输入：
    securityID -- 证券代码
    fields -- 数据项，可以是一个列表
    specificDate -- 数据获取日，为YYYYMMDD字符串,
    
    输出：
    pandas DataFrame格式二维列表
    
    '''
    
    httpClient = __getConn__()
    
    functionName = 'MarketDataGetHistTicks'
    
    requestString = Config.__function_config__[functionName][Config.__server__]['api']
    requestString += "securityID=" + securityID
    requestString += "&field="
    if hasattr(fields, '__iter__'):
        if fields != None:
            for field in fields:
                requestString += field + ","
            requestString = requestString[:-1]
    else:
        if fields != None:
            requestString += fields
    requestString += "&date=" + specificDate

    csvString = __getCSV__(requestString, httpClient)
    
    try:
        myIO = StringIO.StringIO(csvString)
        pdFrame = pd.read_csv(myIO, encoding= encoding, parse_dates = [0], dtype = {'ticker':'str'})
        pdFrame.index.name = 'index'
        return pdFrame
    finally:
        myIO.close()

    
def MarketDataGetDaySnapShot(securityIDs, specificDate, fields):
    '''
    
    获取历史数据API
    输入：
    securityIDs -- 证券代码, 
    fields -- 数据项，可以是一个列表
    specificDate -- 数据获取日，为YYYYMMDD字符串,
    
    输出：
    pandas DataFrame格式二维列表
    
    '''
    
    httpClient = __getConn__()
    
    functionName = 'MarketDataGetDaySnapShot'
    
    requestString = Config.__function_config__[functionName][Config.__server__]['api']
    requestString += "securityID="
    if hasattr(securityIDs,'__iter__'):
        for security in securityIDs:
            requestString += security + ","
        requestString = requestString[:-1]
    else:
        requestString += securityIDs
    requestString += '&field='
    if hasattr(fields, '__iter__'):
        if fields != None:
            for field in fields:
                requestString += field + ","
            requestString = requestString[:-1]
    else:
        if fields != None:
            requestString += fields
    requestString += "&date=" + specificDate
    csvString = __getCSV__(requestString, httpClient)
    try:
        myIO = StringIO.StringIO(csvString)
        pdFrame = pd.read_csv(myIO, encoding= encoding, parse_dates = [0], dtype = {'ticker':'str'})
        pdFrame.index.name = 'index'
        return pdFrame
    finally:
        myIO.close()
    pass

def FundamentalBalanceSheetRange(securityID,
                                 startDate,
                                 endDate,
                                 fields = None,
                                 reportType = 'A'):
    
    '''
    
    获取历史资产负债表API
    输入：
    securityIDs -- 证券代码, 
    startDate   -- 数据获取开始日，为YYYYMMDD字符串
    endDate     -- 数据获取截止日期，为YYYYMMDD字符串
    fields      -- 数据项，可以是一个列表
    reportType  -- 报表类型，'A' = 年报, 'S' = 半年报, 'Q' = 季报
    
    输出：
    pandas DataFrame格式二维列表
    
    '''
    
    httpClient = __getConn__()
    
    functionName = 'FundamentalBalanceSheetRange'
    
    requestString = Config.__function_config__[functionName][Config.__server__]['api']
    requestString += "stockID=" + securityID
    requestString += "&startDate=" +startDate
    requestString += "&endDate=" + endDate
    requestString += '&reportType=' + reportType
    requestString += "&field="
    if hasattr(fields, '__iter__'):
        if fields != None:
            for field in fields:
                requestString += field + ","
            requestString = requestString[:-1]
    else:
        if fields != None:
            requestString += fields
    csvString = __getCSV__(requestString, httpClient)
    try:
        myIO = StringIO.StringIO(csvString)
        pdFrame = pd.read_csv(myIO, encoding= encoding, parse_dates = [0], dtype = {'ticker':'str'})
        pdFrame.index.name = 'index'
        return pdFrame
    finally:
        myIO.close()
    pass
    
def SecurityCategory(standard,
                     level = 1,
                     date = None,
                     fields = None):
    httpClient = __getConn__()
    
    functionName = 'SecurityCategory'
    
    requestString = Config.__function_config__[functionName][Config.__server__]['api']
    requestString += "standard=" + standard + str(level)
    requestString += "&date="
    if date != None:
        requestString += str(date)
    requestString += "&field="
    if hasattr(fields, '__iter__'):
        if fields != None:
            for field in fields:
                requestString += field + ","
            requestString = requestString[:-1]
    else:
        if fields != None:
            requestString += fields
    csvString = __getCSV__(requestString, httpClient)
    try:
        myIO = StringIO.StringIO(csvString)
        pdFrame = pd.read_csv(myIO, encoding= encoding, parse_dates = [0], dtype = {'ticker':'str'})
        pdFrame.index.name = 'index'
        return pdFrame
    finally:
        myIO.close()
    pass

def lowcase_keys(d):
    result = {}
    for key, value in d.items():
        lower_key = key.lower()
        result[lower_key] = value
    return result

def Plot(data, settings = {}):
    
    font = None
    if platform.system() == "Windows":
        font = FontProperties(fname=r"c:\windows\fonts\simsun.ttc", size=14)
    elif platform.system() == 'Linux':
        font = FontProperties(fname=r"/usr/share/fonts/truetype/wqy/wqy-microhei.ttc", size=10)
    elif platform.system() == 'SunOS':
        font = FontProperties(fname=r"/root/wqy-microhei.ttc", size=10)
    else:
        raise Exception("#Unknown system! We don't know where to look for the chinese font")
    
    lowerSettings = lowcase_keys(settings)
    
    if lowerSettings.has_key("figsize"):
        defaultSize = lowerSettings["figsize"]
    else:
        defaultSize = (9,9)

    if lowerSettings.has_key("labels"):
        labels = lowerSettings["labels"]
    else:
        labels = None
    
    if lowerSettings.has_key("y"):
        columns = lowerSettings["y"]
    else:
        columns = None
        
    if lowerSettings.has_key("x"):
        x = lowerSettings["x"]
    else:
        x = None
        
    if lowerSettings.has_key("kind"):
        kind = lowerSettings["kind"]
    else:
        kind = "Line"
        
    if lowerSettings.has_key("title"):
        title  = lowerSettings["title"]
    else:
        title  = None
        
    if lowerSettings.has_key("ylim"):
        ylim  = lowerSettings["ylim"]
    else:
        ylim  = None
        
    if lowerSettings.has_key("xlim"):
        xlim  = lowerSettings["xlim"]
    else:
        xlim  = None
 
    if lowerSettings.has_key("subplots"):
        subplots  = lowerSettings["subplots"]
    else:
        subplots  = False 
        
    if lowerSettings.has_key("secondary_y"):
        secondary_y  = lowerSettings["secondary_y"]
    else:
        secondary_y  = False
        
    if lowerSettings.has_key("style "):
        style   = lowerSettings["style "]
    else:
        style   = None
        
    if lowerSettings.has_key("fontsize"):
        fontSize  = lowerSettings["fontsize"]
    else:
        fontSize  = None 
        
    if fontSize != None:
        font.set_size(fontSize)
        
    legend = True
    
    if columns != None and  secondary_y != False:
        raise Exception('#Curently we cannot handle y and secondary_y together')
        
    if isinstance(data, pd.DataFrame):
        
        if kind.upper() == 'PIE':
            
            # set figure size

            fig = pylab.gcf()
            fig.set_size_inches(defaultSize)
            
            if labels == None:
                labels = data.index
            else:
                labels = data[labels]
            patches, texts= pylab.pie(x = data[x], labels = labels)
            
            for text in texts:
                text.set_fontproperties(font)
            
            if len(labels) <= 6:
                pylab.legend(labels, loc= 0, prop = font)
            
        elif kind.upper() == 'BAR' or kind.upper() == 'BARH':
            if columns != None:
                tmpDF = pd.DataFrame(data[columns])
            else:
                tmpDF = data.copy()
            
            if x != None:
                tmpDF.index = data[x]
                try:
                    tmpDF = tmpDF.drop(x,1)
                except:
                    pass
                
            ax = tmpDF.plot(legend = legend, kind = kind, xlim = xlim, ylim = ylim, 
                  subplots = subplots, secondary_y = secondary_y, style = style, figsize = defaultSize, fontsize = fontSize)
            patches, labels = ax.get_legend_handles_labels()
            if hasattr(columns,'__iter__'):
                ax.legend(patches, columns, loc='best', prop = font)
            elif columns == None:
                pass
            else:
                ax.legend(patches, [columns], loc='best', prop = font)
        elif kind.upper() != 'SCATTER':
            if columns != None:
                tmpDF = pd.DataFrame(data[columns])
            else:
                tmpDF = data.copy()
            
            if x != None:
                tmpDF.index = data[x]
                try:
                    tmpDF = tmpDF.drop(x,1)
                except:
                    pass
                
            tmpDF.plot(legend = legend, kind = kind, xlim = xlim, ylim = ylim, 
                  subplots = subplots, secondary_y = secondary_y, style = style, figsize = defaultSize, fontsize = fontSize)
            if hasattr(columns,'__iter__'):
                pylab.legend(columns, loc = 0, prop = font)
            elif columns == None:
                pass
            else:
                pylab.legend([columns], prop = font)
        else:
            data.plot(x = x, y = columns, legend = legend, kind = kind, xlim = xlim, ylim = ylim, 
                  subplots = subplots, secondary_y = secondary_y, style = style, figsize = defaultSize, fontsize = fontSize)
            
            if hasattr(columns,'__iter__'):
                pylab.legend(columns, loc = 0, prop = font)
            elif columns == None:
                pass
            else:
                pylab.legend([columns], prop = font)
                
        pylab.title(title, fontproperties=font)
        pylab.show()
        
    else:
        raise Exception('#Plot function only support pandas DataFrame object')

    
if __name__ == '__main__':
    
    res = FundamentalBalanceSheetRange(securityID = '600110',
                                   startDate = '20050101',
                                   endDate = '20140101',
                                   reportType = 'Q')
    
    Plot(res, settings= {'x':u'END_DATE', 'y':[u'TOTAL_ASSETS',u'TOTAL_LIAB', u'TOTAL_EQUITY'], 
                     'kind':'Bar', 'title':u'浦发银行2007~2013季度报表'})
    
    res =  MarketDataGetHistDailyQuotes(securityID = "000002.XSHE", 
              fields = ["shortNM", "closePrice", "openPrice", "lowPrice"], 
              startDate = "20000106", 
              endDate = "20140110")
    print res
    
    res =  MarketDataGetHistDailyQuotes(securityID = "120014", 
              fields = None,
              startDate = "20000106", 
              endDate = "20140110")
    print res
    
    Plot(res, settings = {'y':['cleanPrice', 'dirtyPrice']})
    
    #Plot(res, settings = {'x':'tradeDate','y':'closePrice', 'title':u'万科历史收盘价格', 'fontsize':20})
    
    res =  MarketDataGetHistTicks(securityID = "000002.XSHE", 
              specificDate = "20130729")
    print res

 
    res = MarketDataGetDaySnapShot(securityIDs = ['000001.XSHE', '000002.XSHG'],
                                   specificDate = '20140106',
                                   fields = ['closePrice','openPrice', 'shortNM'])
    print res
    
    #Plot(res, settings = {'x':'ticker', 'kind':'bar','secondary_y':'openPrice'})
    res = FundamentalBalanceSheetRange(securityID = '000001', 
                                       startDate = '20050101',
                                       endDate = '20140101')
    
    print res
    
    res =  MarketDataGetHistDailyQuotes(securityID = "000002.XSHE", 
                                    fields = ["shortNM", "closePrice"], 
                                    startDate = "20000106", 
                                    endDate = "20140110")
    
    closePrice = res['closePrice']
    dailyReturn = closePrice[:-1].values / closePrice[1:] - 1
    res['return'] = dailyReturn
    
    Plot(res, settings = {'x':'closePrice', 'y':'return', 'kind':'Scatter', 'title':u'价格 vs. 收益率（散点图）','fontsize':20})
    
    res = SecurityCategory(standard = 'SW', level = 1)
    countDF = res.groupby('industryName')
    ticker = pd.DataFrame(countDF['ticker'].count())
    ticker.columns = ['No. of Corp.']
    ticker['industryName'] = ticker.index
    print ticker
    Plot(ticker, settings = {'title':u'Pie实例', 'x':'No. of Corp.', 'labels':'industryName', 'kind':'Pie'})

