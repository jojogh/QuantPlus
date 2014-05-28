using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using ExcelDna.Integration;
using ExcelDna.ComInterop;
using System.Net;
using System.IO;
using CAL;


namespace CALProxy
{

    #region Data API

    [Guid("9ec85cd5-683d-451a-9b32-79dcc2aa3607")]
    [ClassInterface(ClassInterfaceType.AutoDual)]
    public class DataAPI
    {

        private string server = "staging";
        private readonly Dictionary<string, Dictionary<string, string>> server_config =
            new Dictionary<string, Dictionary<string, string> >()
            {
                {
                    "staging", new Dictionary<string, string>() 
                                   { {"host",  "http://dataapi01.cloud-stg.datayes.com"}, {"port", ""} }
                }
            };
        private readonly Dictionary<string, Dictionary<string, string>> api_config =
            new Dictionary<string, Dictionary<string, string> >() 
            {
                {
                    "MarketDataGetHistDailyQuotes", new Dictionary<string, string>()
                                    {
                                        {"staging", "/market/getDailyQuotesDateRange.csv?" }
                                    }
                },
                {
                    "SecurityCategory", new Dictionary<string, string>()
                                    {
                                        {"staging", "/master/getStocksByStandard.csv?" }
                                    }
                 },
                  {
                    "FundamentalBalanceSheetRange", new Dictionary<string, string>()
                                    {
                                        {"staging", "/fundamental/getBalanceSheetDateRange.csv?" }
                                    }
                 }
            };

        public object[,] MarketDataGetHistDailyQuotes(string securityID, string fieldsStr, DateUtilities.CALDate startDate, DateUtilities.CALDate endDate)
        {
            Dictionary<string, string> tmp = server_config[server];
            string requestString = tmp["host"];
            requestString = (tmp["port"] != "" ? requestString + ":" + tmp["port"] : requestString);
            requestString = requestString + api_config["MarketDataGetHistDailyQuotes"][server];
            requestString = requestString + "securityID=" + securityID;
            requestString = requestString + "&field=";
            string[] fields = fieldsStr.Split(',');
            if (fields.Length != 0)
            {
                foreach (object field in fields)
                {
                    string tmpStr = field.ToString();
                    requestString = requestString + tmpStr + ",";
                }
                requestString = requestString.Remove(requestString.Length - 1);
            }

            requestString = requestString + "&startDate=" +startDate.plainRepr();
            requestString = requestString + "&endDate=" + endDate.plainRepr();
            WebRequest wReq = System.Net.WebRequest.Create(requestString);
            WebResponse wResp = wReq.GetResponse();
            Stream respStream = wResp.GetResponseStream();
            return CSVHelper.parseCSVString(respStream);
         }

        public object[,] SecurityCategory(string standard, int level, string fieldsStr, DateUtilities.CALDate date)
        {
            Dictionary<string, string> tmp = server_config[server];
            string requestString = tmp["host"];
            requestString = (tmp["port"] != "" ? requestString + ":" + tmp["port"] : requestString);
            requestString = requestString + api_config["SecurityCategory"][server];
            requestString = requestString + "standard=" + standard + level;
            requestString = requestString + "&date=" + date.plainRepr();
            requestString = requestString + "&field=";
            string[] fields = fieldsStr.Split(',');
            if (fields.Length != 0)
            {
                foreach (object field in fields)
                {
                    string tmpStr = field.ToString();
                    requestString = requestString + tmpStr + ",";
                }
                requestString = requestString.Remove(requestString.Length - 1);
            }

            WebRequest wReq = System.Net.WebRequest.Create(requestString);
            WebResponse wResp = wReq.GetResponse();
            Stream respStream = wResp.GetResponseStream();
            return CSVHelper.parseCSVString(respStream);
        }

        public object[,] FundamentalBalanceSheetRange(string securityID,
                                                                                    DateUtilities.CALDate startDate,
                                                                                    DateUtilities.CALDate endDate,
                                                                                    string fieldsStr,
                                                                                    string reportType)
        {
            Dictionary<string, string> tmp = server_config[server];
            string requestString = tmp["host"];
            requestString = (tmp["port"] != "" ? requestString + ":" + tmp["port"] : requestString);
            requestString = requestString + api_config["FundamentalBalanceSheetRange"][server];
            requestString = requestString + "stockID=" + securityID;
            requestString = requestString + "&startDate=" + startDate.plainRepr();
            requestString = requestString + "&endDate=" + endDate.plainRepr();
            requestString = requestString + "&reportType=" + reportType;
            requestString = requestString + "&field=";
            string[] fields = fieldsStr.Split(',');
            if (fields.Length != 0)
            {
                foreach (object field in fields)
                {
                    string tmpStr = field.ToString();
                    requestString = requestString + tmpStr + ",";
                }
                requestString = requestString.Remove(requestString.Length - 1);
            }
            WebRequest wReq = System.Net.WebRequest.Create(requestString);
            WebResponse wResp = wReq.GetResponse();
            Stream respStream = wResp.GetResponseStream();
            //return requestString;
            return CSVHelper.parseCSVString(respStream);
        }
    }

    #endregion Data API

    #region Data API Excel

    public static class DataAPIEx
    {
        public static object CALMarketDataGetHistDailyQuotes(string securityID, string fieldsStr, int start, int end)
        {
            try
            {
                if (ExcelDnaUtil.IsInFunctionWizard()) 
                    return "!!! In FunctionWizard";
                DataAPI tmp = new DataAPI();
                DateUtilities.CALDate startDate = new DateUtilities.CALDate(start);
                DateUtilities.CALDate endDate = new DateUtilities.CALDate(end);
                return Utilities.ArrayResizer.Resize(tmp.MarketDataGetHistDailyQuotes(securityID, fieldsStr, startDate, endDate));
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }
        }

        public static object CALSecurityCategory(string standard, int level, string fieldsStr, int date)
        {
            try
            {
                if (ExcelDnaUtil.IsInFunctionWizard())
                    return "!!! In FunctionWizard";
                DataAPI tmp = new DataAPI();
                DateUtilities.CALDate snapDate = new DateUtilities.CALDate(date);
                return Utilities.ArrayResizer.Resize(tmp.SecurityCategory(standard, level, fieldsStr, snapDate));
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }

        }

        public static object CALFundamentalBalanceSheetRange(string securityID, int start, int end, string fieldsStr, string reportType)
        {
            try
            {
                if (ExcelDnaUtil.IsInFunctionWizard())
                    return "!!! In FunctionWizard";
                DataAPI tmp = new DataAPI();
                DateUtilities.CALDate startDate = new DateUtilities.CALDate(start);
                DateUtilities.CALDate endDate = new DateUtilities.CALDate(end);
                //return tmp.FundamentalBalanceSheetRange(securityID, startDate, endDate, fieldsStr, reportType);
                return Utilities.ArrayResizer.Resize(tmp.FundamentalBalanceSheetRange(securityID, startDate, endDate, fieldsStr, reportType));
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }
        }
    }

    #endregion Data API Excel
}
