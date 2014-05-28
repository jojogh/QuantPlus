using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using ExcelDna.Integration;
using ExcelDna.ComInterop;

using CAL;

namespace CALProxy
{

    #region Date Utilities

    [Guid("ada86aed-453d-47cf-8dea-04bd66e4229e")]
    [ClassInterface(ClassInterfaceType.AutoDual)]
    public class DateUtilities
    {
        #region Date
        public CALDate Date(int year, int month, int day)
        {
            return new CALDate(year,month,day);
        }

        public CALDate DateFromSerialNumber(int serialNumber)
        {
            return new CALDate(serialNumber);
        }

        [Guid("7ef20a32-9fdf-47d1-84ab-cf7d51711644")]
        [ClassInterface(ClassInterfaceType.AutoDual)]
        public class CALDate
        {
            internal Date innerDate_;

            public override string ToString()
            {
                return innerDate_.ISO();
            }

            public CALDate()
            {
                innerDate_ = new Date();
            }

            public CALDate(int year, int month, int day)
            {
                innerDate_ = new Date(day, (Month)month, year);
            }

            public CALDate(int serialNumber)
            {
                innerDate_ = new Date(serialNumber);
            }

            public int Year()
            {
                return innerDate_.year();
            }

            public int Month()
            {
                return (int)innerDate_.month();
            }

            public int DayOfMonth()
            {
                return innerDate_.dayOfMonth();
            }

            public int Weekday()
            {
                return innerDate_.weekdayNumber() - 1;
            }

            public int SerialNumber()
            {
                return innerDate_.serialNumber();
            }

            public string plainRepr()
            {
                string tmp = this.ToString();
                return tmp.Replace("-","");
            }
        }

        #endregion date

        #region Calendar
        public CALCalendar Calendar(string name)
        {
            return new CALCalendar(name);
        }

        [Guid("8132f759-b7fe-4697-83de-df1f5bd77b8e")]
        [ClassInterface(ClassInterfaceType.AutoDual)]
        public class CALCalendar
        {
            internal Calendar innerCal_;

            public override string ToString()
            {
                return innerCal_.name();
            }
 

            public CALCalendar(string name)
            {
                innerCal_ = Utilities.parseCalendarByString(name);
            }

            public bool IsHoliday(CALDate caldate)
            {
                return innerCal_.isHoliday(caldate.innerDate_);
            }

            public bool IsBizDay(CALDate caldate)
            {
                return innerCal_.isBusinessDay(caldate.innerDate_);
            }

            public CALDate DateAdvance(CALDate today, string periodrepr, string covrepr = "Following", bool endOfMonth = false)
            {
                Period period = PeriodParser.parse(periodrepr);
                BusinessDayConvention conv = Utilities.parseBizDayConv(covrepr);
                Date calDate = innerCal_.advance(today.innerDate_, period, conv, endOfMonth);
                return new CALDate(calDate.serialNumber());
            }

            public CALDate[] BizDatesList(CALDate startDate, CALDate endDate)
            {
                List<CALDate> bizDates = new List<CALDate>();

                CALDate loopDate = startDate;
                if (this.IsBizDay(loopDate))
                    bizDates.Add(loopDate);
                loopDate = this.DateAdvance(loopDate, "1D");
                while (loopDate.innerDate_.serialNumber() <= endDate.innerDate_.serialNumber())
                {
                    bizDates.Add(loopDate);
                    loopDate = this.DateAdvance(loopDate, "1D");
                }

                return bizDates.ToArray();
            }
        }
        #endregion Calendar
    }
    
    #endregion Date Utilities

    #region Date Utilities Excel
    public static class DateUtilitiesEx
    {
        #region Date
        public static object CALDateYear(int serialNumber)
        {
            try {
                Date calDate = new Date(serialNumber);
                return calDate.year();
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }
        }

        public static object CALDateMonth(int serialNumber)
        {
            try
            {
                Date calDate = new Date(serialNumber);
                return (int)calDate.month();
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }
        }

        public static object CALDateDayOfMonth(int serialNumber)
        {
            try
            {
                Date calDate = new Date(serialNumber);
                return calDate.dayOfMonth();
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }
        }

        public static object CALDateWeekday(int serialNumber)
        {
            try
            {
                Date calDate = new Date(serialNumber);
                return calDate.weekdayNumber() - 1;
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }
        }
        #endregion Date

        #region Calendar

        public static object CALIsHoliday(string calName, int serialNumber)
        {
            try
            {
                DateUtilities.CALCalendar cal = new DateUtilities.CALCalendar(calName);
                DateUtilities.CALDate calDate = new DateUtilities.CALDate(serialNumber);
                return cal.IsHoliday(calDate);
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }
        }

        public static object CALIsBizDay(string calName, int serialNumber)
        {
            try
            {
                DateUtilities.CALCalendar cal = new DateUtilities.CALCalendar(calName);
                DateUtilities.CALDate calDate = new DateUtilities.CALDate(serialNumber);
                return cal.IsBizDay(calDate);
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }
        }

        public static object CALDateAdvance(string calName, int serialNumber, string periodrepr, object covrepr, object endOfMonth)
        {
            try
            {
                //if (ExcelDnaUtil.IsInFunctionWizard()) 
                //    return "!!! In FunctionWizard";
                DateUtilities.CALCalendar cal = new DateUtilities.CALCalendar(calName);
                DateUtilities.CALDate calDate = new DateUtilities.CALDate(serialNumber);
                string cStr = Utilities.Check(covrepr, "Following");
                bool eom = Utilities.Check(endOfMonth, false);
                return cal.DateAdvance(calDate, periodrepr, cStr, eom).SerialNumber();
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }
        }

        public static object CALBizDatesList(string calName, int start, int end)
        {
            try
            {
                //if (ExcelDnaUtil.IsInFunctionWizard()) 
                //    return "!!! In FunctionWizard";
                DateUtilities.CALCalendar cal = new DateUtilities.CALCalendar(calName);
                DateUtilities.CALDate beginDate = new DateUtilities.CALDate(start);
                DateUtilities.CALDate endDate = new DateUtilities.CALDate(end);
                DateUtilities.CALDate[] dateList = cal.BizDatesList(beginDate, endDate);
                double[,] ret = new double[dateList.Length, 1];
                for (int i = 0; i < dateList.Length; ++i)
                {
                    ret[i, 0] = (double)dateList[i].SerialNumber();
                }
                return Utilities.ArrayResizer.ResizeDoubles(ret);
            }
            catch (Exception e)
            {
                return Utilities.ExcelRangeErrorString(e);
            }
            
        }

        #endregion Calendar
    }

    #endregion Date Utilities Excel

}
