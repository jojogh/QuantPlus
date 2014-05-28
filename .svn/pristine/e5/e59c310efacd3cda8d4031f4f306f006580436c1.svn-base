'''
Created on Mar 25, 2014

@author: root
'''

from CAL import *

# Server setup
__server__ = 'staging'

__server_config__ = {
  'dev':{'host':'ds03-dev.datayes.com','port':8080},
  'staging':{'host':'dataapi01.cloud-stg.datayes.com', 'port':None},
  'production':{'host':'dataapi01.cloud-data.datayes.com', 'port':None}}

__function_config__ = {
  'MarketDataGetHistDailyQuotes':{
       'staging':{'api':'/market/getDailyQuotesDateRange.csv?'},
       'production':{'api':'/market/getDailyQuotesDateRange.csv?'},
       'dev':{'api':'/api/market/getDailyQuotesDateRange.csv?'}},
  'MarketDataGetHistTicks':{
       'staging':{'api':'/market/getHistoryTicksOneDay.csv?'},
       'production':{'api':'/market/getHistoryTicksOneDay.csv?'},
       'dev':{'api':'/api/market/getHistoryTicksOneDay.csv?'}},
  'MarketDataGetDaySnapShot':{
       'staging':{'api':'/market/getDailyQuotes.csv?'},
       'production':{'api':'/market/getDailyQuotes.csv?'},
       'dev':{'api':'/api/market/getDailyQuotes.csv?'}},
  'FundamentalBalanceSheetRange':{
       'staging':{'api':'/fundamental/getBalanceSheetDateRange.csv?'},
       'production':{'api':'/fundamental/getBalanceSheetDateRange.csv?'},
       'dev':{'api':'/api/fundamental/getBalanceSheetDateRange.csv?'}},
  'SecurityCategory':{
       'staging':{'api':'/master/getStocksByStandard.csv?'},
       'production':{'api':'/master/getStocksByStandard.csv?'},
       'dev':{'api':'/api/master/getStocksByStandard.csv?'}}}

# Holiday centers setup
__holidayCenterStrs__ = {'CHINA.SSE': (China, China.SSE),
                         'CHINA.IB': (China, China.IB)}

__holidayCenterCodes__ = {10: (China, China.SSE),
                          11: (China, China.IB)}

# MySQL server configure
DB_USER = 'cheng.li_fixedin'
DB_PWD = 'JQrInblr8dIoECWN'
HOST = '10.20.111.101'
DB_NAME = 'securitymaster2'
