using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Diagnostics;
using System.IO;
using ExcelDna.Integration;
using Microsoft.VisualBasic.FileIO;

using CAL;

namespace CALProxy
{
    public static class Utilities
    {
        internal static Calendar parseCalendarByString(string name)
        {
            string lowerName = name.ToLower();
            if (lowerName == "china.sse" || lowerName == "china::sse")
                return new China(China.Market.SSE);
            else if (lowerName == "china.ib" || lowerName == "china::ib")
                return new China(China.Market.IB);
            else
                throw new Exception("#holiday center name" + name + " not matched");
        }

        internal static BusinessDayConvention parseBizDayConv(string name)
        {
            string lowerName = name.ToLower();
            if (lowerName == "following")
                return BusinessDayConvention.Following;
            else if (lowerName == "modifiedfollowing")
                return BusinessDayConvention.ModifiedFollowing;
            else if (lowerName == "unadjusted")
                return BusinessDayConvention.Unadjusted;
            else if (lowerName == "preceding")
                return BusinessDayConvention.Preceding;
            else if (lowerName == "modifiedpreceding")
                return BusinessDayConvention.ModifiedPreceding;
            else
                throw new Exception("#business day convention" + name + " not matched");
                
        }

        internal static string ExcelRangeErrorString(Exception ex)
        {
            string errorMessage = ex.ToString();
            return errorMessage;
        }

        internal static string Check(object arg, string defaultValue)
        {
            if (arg is string)
                return (string)arg;
            else if (arg is ExcelMissing)
                return defaultValue;
            else
                return arg.ToString();  // Or whatever you want to do here....

            // Perhaps check for other types and do whatever you think is right ....
            //else if (arg is double)
            //    return "Double: " + (double)arg;
            //else if (arg is bool)
            //    return "Boolean: " + (bool)arg;
            //else if (arg is ExcelError)
            //    return "ExcelError: " + arg.ToString();
            //else if (arg is object[,])
            //    // The object array returned here may contain a mixture of types,
            //    // reflecting the different cell contents.
            //    return string.Format("Array[{0},{1}]", 
            //      ((object[,])arg).GetLength(0), ((object[,])arg).GetLength(1));
            //else if (arg is ExcelEmpty)
            //    return "<<Empty>>"; // Would have been null
            //else if (arg is ExcelReference)
            //  // Calling xlfRefText here requires IsMacroType=true for this function.
            //				return "Reference: " + 
            //                     XlCall.Excel(XlCall.xlfReftext, arg, true);
            //			else
            //				return "!? Unheard Of ?!";
        }

        internal static double Check(object arg, double defaultValue)
        {
            if (arg is double)
                return (double)arg;
            else if (arg is ExcelMissing)
                return defaultValue;
            else
                throw new ArgumentException();  // Will return #VALUE to Excel

        }

        internal static bool Check(object arg, bool defaultValue)
        {
            if (arg is bool)
                return (bool)arg;
            else if (arg is ExcelMissing)
                return defaultValue;
            else
                throw new ArgumentException();  // Will return #VALUE to Excel

        }

        // This one is more tricky - we have to do the double->Date conversions ourselves
        internal static DateTime Check(object arg, DateTime defaultValue)
        {
            if (arg is double)
                return DateTime.FromOADate((double)arg);    // Here is the conversion
            else if (arg is string)
                return DateTime.Parse((string)arg);
            else if (arg is ExcelMissing)
                return defaultValue;

            else
                throw new ArgumentException();  // Or defaultValue or whatever
        }

        internal class ArrayResizer : XlCall
        {
            // This function will run in the UDF context.
            // Needs extra protection to allow multithreaded use.
            internal static object Resize(object[,] array)
            {
                var caller = Excel(xlfCaller) as ExcelReference;
                if (caller == null)
                    return array;

                int rows = array.GetLength(0);
                int columns = array.GetLength(1);

                if (rows == 0 || columns == 0)
                    return array;

                if ((caller.RowLast - caller.RowFirst + 1 == rows) &&
                    (caller.ColumnLast - caller.ColumnFirst + 1 == columns))
                {
                    // Size is already OK - just return result
                    return array;
                }

                var rowLast = caller.RowFirst + rows - 1;
                var columnLast = caller.ColumnFirst + columns - 1;

                // Check for the sheet limits
                if (rowLast > ExcelDnaUtil.ExcelLimits.MaxRows - 1 ||
                    columnLast > ExcelDnaUtil.ExcelLimits.MaxColumns - 1)
                {
                    // Can't resize - goes beyond the end of the sheet - just return #VALUE
                    // (Can't give message here, or change cells)
                    return ExcelError.ExcelErrorValue;
                }

                // TODO: Add some kind of guard for ever-changing result?
                ExcelAsyncUtil.QueueAsMacro(() =>
                {
                    // Create a reference of the right size
                    var target = new ExcelReference(caller.RowFirst, rowLast, caller.ColumnFirst, columnLast, caller.SheetId);
                    DoResize(target); // Will trigger a recalc by writing formula
                });
                // Return what we have - to prevent flashing #N/A
                return array;
            }

            internal static double[,] ResizeDoubles(double[,] array)
            {
                var caller = Excel(xlfCaller) as ExcelReference;
                if (caller == null)
                    return array;

                int rows = array.GetLength(0);
                int columns = array.GetLength(1);

                if (rows == 0 || columns == 0)
                    return array;

                if ((caller.RowLast - caller.RowFirst + 1 == rows) &&
                    (caller.ColumnLast - caller.ColumnFirst + 1 == columns))
                {
                    // Size is already OK - just return result
                    return array;
                }

                var rowLast = caller.RowFirst + rows - 1;
                var columnLast = caller.ColumnFirst + columns - 1;

                if (rowLast > ExcelDnaUtil.ExcelLimits.MaxRows - 1 ||
                    columnLast > ExcelDnaUtil.ExcelLimits.MaxColumns - 1)
                {
                    // Can't resize - goes beyond the end of the sheet - just return null (for #NUM!)
                    // (Can't give message here, or change cells)
                    return null;
                }

                // TODO: Add guard for ever-changing result?
                ExcelAsyncUtil.QueueAsMacro(() =>
                {
                    // Create a reference of the right size
                    var target = new ExcelReference(caller.RowFirst, rowLast, caller.ColumnFirst, columnLast, caller.SheetId);
                    DoResize(target); // Will trigger a recalc by writing formula
                });
                // Return what we have - to prevent flashing #N/A
                return array;
            }

            static void DoResize(ExcelReference target)
            {
                // Get the current state for reset later
                using (new ExcelEchoOffHelper())
                using (new ExcelCalculationManualHelper())
                {
                    ExcelReference firstCell = new ExcelReference(target.RowFirst, target.RowFirst, target.ColumnFirst, target.ColumnFirst, target.SheetId);

                    // Get the formula in the first cell of the target
                    string formula = (string)Excel(xlfGetCell, 41, firstCell);
                    bool isFormulaArray = (bool)Excel(xlfGetCell, 49, firstCell);
                    if (isFormulaArray)
                    {
                        // Select the sheet and firstCell - needed because we want to use SelectSpecial.
                        using (new ExcelSelectionHelper(firstCell))
                        {
                            // Extend the selection to the whole array and clear
                            Excel(xlcSelectSpecial, 6);
                            ExcelReference oldArray = (ExcelReference)Excel(xlfSelection);

                            oldArray.SetValue(ExcelEmpty.Value);
                        }
                    }
                    // Get the formula and convert to R1C1 mode
                    bool isR1C1Mode = (bool)Excel(xlfGetWorkspace, 4);
                    string formulaR1C1 = formula;
                    if (!isR1C1Mode)
                    {
                        object formulaR1C1Obj;
                        XlReturn formulaR1C1Return = TryExcel(xlfFormulaConvert, out formulaR1C1Obj, formula, true, false, ExcelMissing.Value, firstCell);
                        if (formulaR1C1Return != XlReturn.XlReturnSuccess || formulaR1C1Obj is ExcelError)
                        {
                            string firstCellAddress = (string)Excel(xlfReftext, firstCell, true);
                            Excel(xlcAlert, "Cannot resize array formula at " + firstCellAddress + " - formula might be too long when converted to R1C1 format.");
                            firstCell.SetValue("'" + formula);
                            return;
                        }
                        formulaR1C1 = (string)formulaR1C1Obj;
                    }
                    // Must be R1C1-style references
                    object ignoredResult;
                    //Debug.Print("Resizing START: " + target.RowLast);
                    XlReturn formulaArrayReturn = TryExcel(xlcFormulaArray, out ignoredResult, formulaR1C1, target);
                    //Debug.Print("Resizing FINISH");

                    // TODO: Find some dummy macro to clear the undo stack

                    if (formulaArrayReturn != XlReturn.XlReturnSuccess)
                    {
                        string firstCellAddress = (string)Excel(xlfReftext, firstCell, true);
                        Excel(xlcAlert, "Cannot resize array formula at " + firstCellAddress + " - result might overlap another array.");
                        // Might have failed due to array in the way.
                        firstCell.SetValue("'" + formula);
                    }
                }
            }
        }

        // RIIA-style helpers to deal with Excel selections    
        // Don't use if you agree with Eric Lippert here: http://stackoverflow.com/a/1757344/44264
        public class ExcelEchoOffHelper : XlCall, IDisposable
        {
            object oldEcho;

            public ExcelEchoOffHelper()
            {
                oldEcho = Excel(xlfGetWorkspace, 40);
                Excel(xlcEcho, false);
            }

            public void Dispose()
            {
                Excel(xlcEcho, oldEcho);
            }
        }

        public class ExcelCalculationManualHelper : XlCall, IDisposable
        {
            object oldCalculationMode;

            public ExcelCalculationManualHelper()
            {
                oldCalculationMode = Excel(xlfGetDocument, 14);
                Excel(xlcOptionsCalculation, 3);
            }

            public void Dispose()
            {
                Excel(xlcOptionsCalculation, oldCalculationMode);
            }
        }

        // Select an ExcelReference (perhaps on another sheet) allowing changes to be made there.
        // On clean-up, resets all the selections and the active sheet.
        // Should not be used if the work you are going to do will switch sheets, amke new sheets etc.
        public class ExcelSelectionHelper : XlCall, IDisposable
        {
            object oldSelectionOnActiveSheet;
            object oldActiveCellOnActiveSheet;

            object oldSelectionOnRefSheet;
            object oldActiveCellOnRefSheet;

            public ExcelSelectionHelper(ExcelReference refToSelect)
            {
                // Remember old selection state on the active sheet
                oldSelectionOnActiveSheet = Excel(xlfSelection);
                oldActiveCellOnActiveSheet = Excel(xlfActiveCell);

                // Switch to the sheet we want to select
                string refSheet = (string)Excel(xlSheetNm, refToSelect);
                Excel(xlcWorkbookSelect, new object[] { refSheet });

                // record selection and active cell on the sheet we want to select
                oldSelectionOnRefSheet = Excel(xlfSelection);
                oldActiveCellOnRefSheet = Excel(xlfActiveCell);

                // make the selection
                Excel(xlcFormulaGoto, refToSelect);
            }

            public void Dispose()
            {
                // Reset the selection on the target sheet
                Excel(xlcSelect, oldSelectionOnRefSheet, oldActiveCellOnRefSheet);

                // Reset the sheet originally selected
                string oldActiveSheet = (string)Excel(xlSheetNm, oldSelectionOnActiveSheet);
                Excel(xlcWorkbookSelect, new object[] { oldActiveSheet });

                // Reset the selection in the active sheet (some bugs make this change sometimes too)
                Excel(xlcSelect, oldSelectionOnActiveSheet, oldActiveCellOnActiveSheet);
            }
        }
    }

    public class CSVHelper : List<string[]>
    {
        public static object[,] parseCSVString(Stream csvStr)
        {
            TextFieldParser parser = new TextFieldParser(csvStr, Encoding.GetEncoding("gb2312"));
            parser.TextFieldType = FieldType.Delimited;
            parser.SetDelimiters(",");
            List<string[]> lineList = new List<string[]>();
            while (!parser.EndOfData)
            {
                //Processing row
                string[] fields = parser.ReadFields();
                lineList.Add(fields);
            }
            parser.Close();

            object[,] ret = new object[lineList.Count, lineList[0].Length];

            for(int i=0;i<lineList.Count;++i) {
                string[] line = lineList[i];
                for (int j = 0; j < line.Length; ++j)
                {
                    try
                    {
                        ret[i, j] = double.Parse(line[j]);
                    }
                    catch (Exception)
                    {
                        ret[i, j] = line[j];
                    }
                        
                }
                   
            }
            return ret;
        }

    }
}
