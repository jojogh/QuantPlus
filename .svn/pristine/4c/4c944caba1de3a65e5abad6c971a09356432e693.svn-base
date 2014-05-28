# -*- coding: utf-8 -*-
'''
Created on 2014-4-14

@author: cheng.li
'''

from Config import DB_USER, DB_PWD, HOST, DB_NAME
import pandas.io.sql as psql
import MySQLdb
from string import Template 
import pandas as pd

class DBConnection:
    def __init__(self):
        self.conn = MySQLdb.connect(host=HOST,user=DB_USER,passwd=DB_PWD,db=DB_NAME, charset="utf8")
    def excute(self, sqlCommend):
        return psql.frame_query(sqlCommend, con = self.conn) 

    def __del__(self):
        if self.conn:
            self.conn.close()

__availablePriceFields__ = {
                     'cleanprice':['CLEAN_PRICE','cleanPrice'],
                     'dirtyprice':['DIRTY_PRICE', 'dirtyPrice'],
                     'duration':['DURATION', 'duration'],
                     'dv01':['DV01', 'dv01'],
                     'yield':['YIELD', 'yield'],
                     'convexity':['CONVEXITY', 'convexity'],
                     'price':['CLEAN_PRICE', 'cleanPrice'],
                     'ytm':['YIELD', 'yield']}

__availableBondStaticInfoFields__ = {
                     'issuer':['ISSUER', 'issuer'],
                     'exchange':['EXCHANGE_CD', 'market'],
                     'market':['EXCHANGE_CD', 'market'],
                     'shortnm':['BOND_NAME', 'shortNM'],
                     'name':['CHINESE_NAME', 'fullName'],
                     'fullname':['CHINESE_NAME', 'fullName'],
                     'accrualtype':['ACCRUAL_TYPE_CD', 'accrualType'],
                     'cpntype':['COUPON_TYPE_CD', 'cpnType'],
                     'cpn':['COUPON', 'coupon'],
                     'cpnfreq':['CPN_FREQ_CD', 'cpnFreq'],
                     'freq':['CPN_FREQ_CD', 'cpnFreq'],
                     'frequency':['CPN_FREQ_CD', 'cpnFreq'],
                     'issueprice':['ISSUE_PRICE','issuePrice'],
                     'issuedate':['ISSUE_DT', 'issueDate'],
                     'firstaccrual':['FIRST_ACCRUAL_DT', 'firstAccrual'],
                     'maturity':['MATURITY_DT', 'maturityDate']}


def __uniqueFields__(rawFields, avaDict):
    newFields = set()
    
    if isinstance(rawFields,str):
        try:
            sqlFieldName = avaDict[rawFields.lower()][0]
            newFields.add((avaDict[rawFields.lower()][1], sqlFieldName))
            return newFields
        except:
            raise Exception("#No field name available for " + rawFields)
    
    if rawFields == None or len(rawFields) == 0:
        for field in avaDict.values():
            newFields.add((field[1], field[0]))
        return newFields
    
    for field in rawFields:
        try:
            sqlFieldName = avaDict[field.lower()][0]
            newFields.add((avaDict[field.lower()][1], sqlFieldName))
        except:
            raise Exception("#No field name available for " + field)
        
    return newFields
            
class BondDBUtilities:
    
    @staticmethod
    def BondStatInfo(ticker, fields = None):
        __dbconn__ = DBConnection()
        sqlTemplate = '''
                      SELECT ticker_symbol $fields
                      FROM securitymaster2.bond where $ticker_name
                      '''
        t = Template(sqlTemplate)
        
        fieldsStr = ","
        columns = ['ticker']
        
        newFields = __uniqueFields__(fields, __availableBondStaticInfoFields__)
            
        for sqlField, fieldName in newFields:
            fieldsStr = fieldsStr + fieldName + ','
            columns.append(sqlField)
        fieldsStr = fieldsStr[:-1]
        d = {'ticker_name':"ticker_symbol = '" + ticker + "'",
             'fields':fieldsStr}
        sql = t.substitute(d) 

        df = __dbconn__.excute(sql)
        df.index.name = 'index'
        df.columns = columns
        return df
    
    @staticmethod
    def HistBondPrice(ticker, startDate, endDate, fields = None):
        __dbconn__ = DBConnection()
        sqlTemplate = '''
                      SELECT DATA_DT, ticker_symbol $fields
                      FROM securitymaster2.bond
                      INNER JOIN securitymaster2.bond_price
                      ON securitymaster2.bond.security_id = securitymaster2.bond_price.security_id  
                      where DATA_DT >= Date('$startDate') and DATA_DT <= Date('$endDate') and ticker_symbol = $ticker_name and price_source_cd = 'CHINABOND'
                      '''
        t = Template(sqlTemplate)
        
        fieldsStr = ","
        columns = ['tradeDate', 'ticker']
        
        newFields = __uniqueFields__(fields, __availablePriceFields__)
            
        for sqlField, fieldName in newFields:
            fieldsStr = fieldsStr + fieldName + ','
            columns.append(sqlField)

        fieldsStr = fieldsStr[:-1]
        startDate = pd.Timestamp(startDate)
        endDate = pd.Timestamp(endDate)
        
        d = {'ticker_name':"'" + ticker + "'",
             'fields': fieldsStr,
             'startDate': startDate.isoformat(),
             'endDate': endDate.isoformat()}
        sql = t.substitute(d) 
        
        df = __dbconn__.excute(sql)
        df.index.name = 'index'
        df.columns = columns
        
        return df

if __name__ == '__main__':
    df = BondDBUtilities.HistBondPrice('120014', '20131213', '20141212', ['YTM', 'Price'])
    print df
    df = BondDBUtilities.BondStatInfo('120014', fields = None)
    print df