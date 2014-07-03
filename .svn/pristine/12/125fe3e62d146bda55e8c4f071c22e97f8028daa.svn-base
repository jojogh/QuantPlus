
/*  
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2006, 2007, 2008, 2009 Ferdinando Ametrano
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Aurelien Chanudet
 Copyright (C) 2013 Cheng Li
 
 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// This file was generated automatically by gensrc.py.  If you edit this file
// manually then your changes will be lost the next time gensrc runs.

// This source code file was generated from the following stub:
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/bonds.hpp>
#include <qlo/yieldtermstructures.hpp>
#include <qlo/indexes/ibor/euribor.hpp>
#include <qlo/indexes/ibor/libor.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/instruments/bonds/fixedratebond.hpp>
#include <ql/indexes/ibor/euribor.hpp>
#include <ql/indexes/ibor/shibor.hpp>
#include <ql/indexes/ibor/repochina.h>
#include <qlo/valueobjects/vo_ratehelpers.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string CALBondHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Price,
            const std::string &Bond,
            const ObjectHandler::property_t &UseCleanPrice,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool UseCleanPriceCpp = ObjectHandler::convert2<bool>(
            UseCleanPrice, "UseCleanPrice", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Price, "Price");

        OH_GET_REFERENCE(BondLibObjPtr, Bond,
            QuantLibAddin::Bond, QuantLib::Bond)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALBondHelper(
                ObjectId,
                Price,
                Bond,
                UseCleanPriceCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BondHelper(
                valueObject,
                PriceLibObj,
                BondLibObjPtr,
                UseCleanPriceCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALBondHelper : " << e.what());
        }
    }


    std::string CALCTBFixedBondHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CleanPrice,
            const ObjectHandler::property_t &IssueDate,
            const long &SettlementDays,
            const ObjectHandler::property_t &FaceAmount,
            const ObjectHandler::property_t &Start,
            const ObjectHandler::property_t &Maturity,
            const std::string &Tenor,
            const std::vector<double>& Coupons,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &EndOfMonth,
            const ObjectHandler::property_t &Calendar,
            const ObjectHandler::property_t &PaymentCalendar,
            const ObjectHandler::property_t &Convention,
            const ObjectHandler::property_t &GenRule,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &FirstDate,
            const ObjectHandler::property_t &NextToLastDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            FaceAmount, "FaceAmount", 100.0);

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/Actual (No Leap)");

        bool EndOfMonthCpp = ObjectHandler::convert2<bool>(
            EndOfMonth, "EndOfMonth", false);

        std::string CalendarCpp = ObjectHandler::convert2<std::string>(
            Calendar, "Calendar", "NullCalendar");

        std::string PaymentCalendarCpp = ObjectHandler::convert2<std::string>(
            PaymentCalendar, "PaymentCalendar", "CHINA");

        std::string ConventionCpp = ObjectHandler::convert2<std::string>(
            Convention, "Convention", "Unadjusted");

        std::string GenRuleCpp = ObjectHandler::convert2<std::string>(
            GenRule, "GenRule", "Backward");

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        double RedemptionCpp = ObjectHandler::convert2<double>(
            Redemption, "Redemption", 100.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate");

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        QuantLib::Date StartLib = ObjectHandler::convert2<QuantLib::Date>(
            Start, "Start");

        QuantLib::Date MaturityLib = ObjectHandler::convert2<QuantLib::Date>(
            Maturity, "Maturity");

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Date FirstDateLib = ObjectHandler::convert2<QuantLib::Date>(
            FirstDate, "FirstDate", QuantLib::Date());

        QuantLib::Date NextToLastDateLib = ObjectHandler::convert2<QuantLib::Date>(
            NextToLastDate, "NextToLastDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(CalendarCpp);

        QuantLib::Calendar PaymentCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(PaymentCalendarCpp);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(ConventionCpp);

        QuantLib::DateGeneration::Rule GenRuleEnum =
            ObjectHandler::Create<QuantLib::DateGeneration::Rule>()(GenRuleCpp);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> CleanPriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                CleanPrice, "CleanPrice");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALCTBFixedBondHelper(
                ObjectId,
                CleanPrice,
                IssueDate,
                SettlementDays,
                FaceAmountCpp,
                Start,
                Maturity,
                Tenor,
                Coupons,
                DayCounterCpp,
                EndOfMonthCpp,
                CalendarCpp,
                PaymentCalendarCpp,
                ConventionCpp,
                GenRuleCpp,
                PaymentBDCCpp,
                RedemptionCpp,
                FirstDate,
                NextToLastDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTBFixedBondHelper(
                valueObject,
                CleanPriceLibObj,
                IssueDateLib,
                SettlementDaysLib,
                FaceAmountCpp,
                StartLib,
                MaturityLib,
                TenorLib,
                Coupons,
                DayCounterEnum,
                EndOfMonthCpp,
                CalendarEnum,
                PaymentCalendarEnum,
                ConventionEnum,
                GenRuleEnum,
                PaymentBDCEnum,
                RedemptionCpp,
                FirstDateLib,
                NextToLastDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALCTBFixedBondHelper : " << e.what());
        }
    }


    std::string CALCTBZeroBondHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CleanPrice,
            const long &SettlementDays,
            const std::string &Calendar,
            const ObjectHandler::property_t &FaceAmount,
            const double &IssuePrice,
            const ObjectHandler::property_t &IssueDate,
            const std::string &DayCounter,
            const ObjectHandler::property_t &MaturityDate,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            FaceAmount, "FaceAmount", 100.0);

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        double RedemptionCpp = ObjectHandler::convert2<double>(
            Redemption, "Redemption", 100.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate");

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            MaturityDate, "MaturityDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> CleanPriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                CleanPrice, "CleanPrice");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALCTBZeroBondHelper(
                ObjectId,
                CleanPrice,
                SettlementDays,
                Calendar,
                FaceAmountCpp,
                IssuePrice,
                IssueDate,
                DayCounter,
                MaturityDate,
                PaymentBDCCpp,
                RedemptionCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTBZeroBondHelper(
                valueObject,
                CleanPriceLibObj,
                SettlementDaysLib,
                CalendarEnum,
                FaceAmountCpp,
                IssuePrice,
                IssueDateLib,
                DayCounterEnum,
                MaturityDateLib,
                PaymentBDCEnum,
                RedemptionCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALCTBZeroBondHelper : " << e.what());
        }
    }


    std::string CALDatedOISRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &EndDate,
            const ObjectHandler::property_t &FixedRate,
            const std::string &ONIndex,
            const ObjectHandler::property_t &DiscountingCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DiscountingCurveCpp = ObjectHandler::convert2<std::string>(
            DiscountingCurve, "DiscountingCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            StartDate, "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            EndDate, "EndDate");

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> FixedRateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                FixedRate, "FixedRate");

        OH_GET_REFERENCE(ONIndexLibObjPtr, ONIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALDatedOISRateHelper(
                ObjectId,
                StartDate,
                EndDate,
                FixedRate,
                ONIndex,
                DiscountingCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DatedOISRateHelper(
                valueObject,
                StartDateLib,
                EndDateLib,
                FixedRateLibObj,
                ONIndexLibObjPtr,
                DiscountingCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALDatedOISRateHelper : " << e.what());
        }
    }


    std::string CALDepositRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALDepositRateHelper(
                ObjectId,
                Rate,
                IborIndex,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DepositRateHelper(
                valueObject,
                RateLibObj,
                IborIndexLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALDepositRateHelper : " << e.what());
        }
    }


    std::string CALDepositRateHelper2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &Tenor,
            const long &FixingDays,
            const std::string &Calendar,
            const std::string &Convention,
            const bool &EndOfMonth,
            const std::string &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(FixingDays, FixingDaysLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALDepositRateHelper2(
                ObjectId,
                Rate,
                Tenor,
                FixingDays,
                Calendar,
                Convention,
                EndOfMonth,
                DayCounter,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DepositRateHelper(
                valueObject,
                RateLibObj,
                TenorLib,
                FixingDaysLib,
                CalendarEnum,
                ConventionEnum,
                EndOfMonth,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALDepositRateHelper2 : " << e.what());
        }
    }


    std::string CALFixedRateBondHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Price,
            const long &SettlementDays,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const std::vector<double>& Coupons,
            const std::string &DayCounter,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const std::string &PaymentCalendar,
            const std::string &ExCouponPeriod,
            const std::string &ExCouponCalendar,
            const std::string &ExCouponBDC,
            const bool &ExCouponEndOfMonth,
            const ObjectHandler::property_t &UseCleanPrice,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            FaceAmount, "FaceAmount", 100.0);

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        double RedemptionCpp = ObjectHandler::convert2<double>(
            Redemption, "Redemption", 100.0);

        bool UseCleanPriceCpp = ObjectHandler::convert2<bool>(
            UseCleanPrice, "UseCleanPrice", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate", QuantLib::Date());

        QuantLib::Period ExCouponPeriodLib;
        QuantLibAddin::cppToLibrary(ExCouponPeriod, ExCouponPeriodLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::Calendar PaymentCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(PaymentCalendar);

        QuantLib::Calendar ExCouponCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(ExCouponCalendar);

        QuantLib::BusinessDayConvention ExCouponBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(ExCouponBDC);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Price, "Price");

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALFixedRateBondHelper(
                ObjectId,
                Price,
                SettlementDays,
                FaceAmountCpp,
                ScheduleID,
                Coupons,
                DayCounter,
                PaymentBDCCpp,
                RedemptionCpp,
                IssueDate,
                PaymentCalendar,
                ExCouponPeriod,
                ExCouponCalendar,
                ExCouponBDC,
                ExCouponEndOfMonth,
                UseCleanPriceCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateBondHelper(
                valueObject,
                PriceLibObj,
                SettlementDaysLib,
                FaceAmountCpp,
                ScheduleIDLibObjPtr,
                Coupons,
                DayCounterEnum,
                PaymentBDCEnum,
                RedemptionCpp,
                IssueDateLib,
                PaymentCalendarEnum,
                ExCouponPeriodLib,
                ExCouponCalendarEnum,
                ExCouponBDCEnum,
                ExCouponEndOfMonth,
                UseCleanPriceCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALFixedRateBondHelper : " << e.what());
        }
    }


    std::string CALFraRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &PeriodToStart,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period PeriodToStartLib;
        QuantLibAddin::cppToLibrary(PeriodToStart, PeriodToStartLib);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALFraRateHelper(
                ObjectId,
                Rate,
                PeriodToStart,
                IborIndex,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FraRateHelper(
                valueObject,
                RateLibObj,
                PeriodToStartLib,
                IborIndexLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALFraRateHelper : " << e.what());
        }
    }


    std::string CALFraRateHelper2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &PeriodToStart,
            const long &LengthInMonths,
            const long &FixingDays,
            const std::string &Calendar,
            const std::string &Convention,
            const bool &EndOfMonth,
            const std::string &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period PeriodToStartLib;
        QuantLibAddin::cppToLibrary(PeriodToStart, PeriodToStartLib);

        QuantLib::Natural LengthInMonthsLib;
        QuantLibAddin::cppToLibrary(LengthInMonths, LengthInMonthsLib);

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(FixingDays, FixingDaysLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALFraRateHelper2(
                ObjectId,
                Rate,
                PeriodToStart,
                LengthInMonths,
                FixingDays,
                Calendar,
                Convention,
                EndOfMonth,
                DayCounter,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FraRateHelper(
                valueObject,
                RateLibObj,
                PeriodToStartLib,
                LengthInMonthsLib,
                FixingDaysLib,
                CalendarEnum,
                ConventionEnum,
                EndOfMonth,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALFraRateHelper2 : " << e.what());
        }
    }


    std::string CALFuturesRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Price,
            const ObjectHandler::property_t &IMM,
            const ObjectHandler::property_t &IborIndex,
            const ObjectHandler::property_t &ConvexityAdjQuote,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string IborIndexCpp = ObjectHandler::convert2<std::string>(
            IborIndex, "IborIndex", "Euribor3M");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date IMMLib = ObjectHandler::convert2<QuantLib::Date>(
            IMM, "IMM");

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Price, "Price");

        OH_GET_REFERENCE_DEFAULT(IborIndexLibObjPtr, IborIndexCpp,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ConvexityAdjQuote, "ConvexityAdjQuote");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALFuturesRateHelper(
                ObjectId,
                Price,
                IMM,
                IborIndexCpp,
                ConvexityAdjQuote,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesRateHelper(
                valueObject,
                PriceLibObj,
                IMMLib,
                IborIndexLibObjPtr,
                ConvexityAdjQuoteLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALFuturesRateHelper : " << e.what());
        }
    }


    std::string CALFuturesRateHelper2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Price,
            const ObjectHandler::property_t &IMM,
            const ObjectHandler::property_t &LengthInMonths,
            const std::string &Calendar,
            const ObjectHandler::property_t &Convention,
            const ObjectHandler::property_t &EndOfMonth,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &ConvexityAdjQuote,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        long LengthInMonthsCpp = ObjectHandler::convert2<long>(
            LengthInMonths, "LengthInMonths", 3);

        std::string ConventionCpp = ObjectHandler::convert2<std::string>(
            Convention, "Convention", "Modified Following");

        bool EndOfMonthCpp = ObjectHandler::convert2<bool>(
            EndOfMonth, "EndOfMonth", true);

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/360");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date IMMLib = ObjectHandler::convert2<QuantLib::Date>(
            IMM, "IMM");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(ConventionCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Price, "Price");

        QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ConvexityAdjQuote, "ConvexityAdjQuote");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALFuturesRateHelper2(
                ObjectId,
                Price,
                IMM,
                LengthInMonthsCpp,
                Calendar,
                ConventionCpp,
                EndOfMonthCpp,
                DayCounterCpp,
                ConvexityAdjQuote,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesRateHelper(
                valueObject,
                PriceLibObj,
                IMMLib,
                LengthInMonthsCpp,
                CalendarEnum,
                ConventionEnum,
                EndOfMonthCpp,
                DayCounterEnum,
                ConvexityAdjQuoteLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALFuturesRateHelper2 : " << e.what());
        }
    }


    std::string CALFuturesRateHelper3(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Price,
            const ObjectHandler::property_t &IMM,
            const ObjectHandler::property_t &EndDate,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &ConvexityAdjQuote,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/360");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date IMMLib = ObjectHandler::convert2<QuantLib::Date>(
            IMM, "IMM");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            EndDate, "EndDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Price, "Price");

        QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ConvexityAdjQuote, "ConvexityAdjQuote");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALFuturesRateHelper3(
                ObjectId,
                Price,
                IMM,
                EndDate,
                DayCounterCpp,
                ConvexityAdjQuote,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesRateHelper(
                valueObject,
                PriceLibObj,
                IMMLib,
                EndDateLib,
                DayCounterEnum,
                ConvexityAdjQuoteLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALFuturesRateHelper3 : " << e.what());
        }
    }


    std::string CALIBFRSwapRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &SwapTenor,
            const std::string &PayFrequency,
            const std::string &RepoIndex,
            const ObjectHandler::property_t &RateSpread,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &DiscountingCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DiscountingCurveCpp = ObjectHandler::convert2<std::string>(
            DiscountingCurve, "DiscountingCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Frequency PayFrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(PayFrequency);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        OH_GET_REFERENCE(RepoIndexLibObjPtr, RepoIndex,
            QuantLibAddin::RepoChina, QuantLib::RepoChina)

        QuantLib::Handle<QuantLib::Quote> RateSpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                RateSpread, "RateSpread");

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALIBFRSwapRateHelper(
                ObjectId,
                Rate,
                SwapTenor,
                PayFrequency,
                RepoIndex,
                RateSpread,
                ForwardStart,
                DiscountingCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IBFRSwapRateHelper(
                valueObject,
                RateLibObj,
                SwapTenorLib,
                PayFrequencyEnum,
                RepoIndexLibObjPtr,
                RateSpreadLibObj,
                ForwardStartLib,
                DiscountingCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALIBFRSwapRateHelper : " << e.what());
        }
    }


    std::string CALOISRateHelper(
            const std::string &ObjectId,
            const long &SettlDays,
            const std::string &Tenor,
            const ObjectHandler::property_t &FixedRate,
            const std::string &ONIndex,
            const ObjectHandler::property_t &DiscountingCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DiscountingCurveCpp = ObjectHandler::convert2<std::string>(
            DiscountingCurve, "DiscountingCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Natural SettlDaysLib;
        QuantLibAddin::cppToLibrary(SettlDays, SettlDaysLib);

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> FixedRateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                FixedRate, "FixedRate");

        OH_GET_REFERENCE(ONIndexLibObjPtr, ONIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALOISRateHelper(
                ObjectId,
                SettlDays,
                Tenor,
                FixedRate,
                ONIndex,
                DiscountingCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OISRateHelper(
                valueObject,
                SettlDaysLib,
                TenorLib,
                FixedRateLibObj,
                ONIndexLibObjPtr,
                DiscountingCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALOISRateHelper : " << e.what());
        }
    }


    double CALRateHelperImpliedQuote(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::RateHelper, QuantLib::RateHelper)

        // invoke the member function

        double returnValue = ObjectIdLibObjPtr->impliedQuote();

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALRateHelperImpliedQuote : " << e.what());
        }
    }


    double CALRateHelperQuoteError(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::RateHelper, QuantLib::RateHelper)

        // invoke the member function

        double returnValue = ObjectIdLibObjPtr->quoteError();

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALRateHelperQuoteError : " << e.what());
        }
    }


    double CALRateHelperQuoteIsValid(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::RateHelper, QuantLib::RateHelper)

        // invoke the member function

        double returnValue = ObjectIdLibObjPtr->quote()->isValid();

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALRateHelperQuoteIsValid : " << e.what());
        }
    }


    double CALRateHelperQuoteValue(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::RateHelper, QuantLib::RateHelper)

        // invoke the member function

        double returnValue = ObjectIdLibObjPtr->quote()->value();

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALRateHelperQuoteValue : " << e.what());
        }
    }


    std::string CALShiborSwapRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &SwapTenor,
            const std::string &FixedLegFrequency,
            const std::string &ShiborIndex,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &DiscountingCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DiscountingCurveCpp = ObjectHandler::convert2<std::string>(
            DiscountingCurve, "DiscountingCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Frequency FixedLegFrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FixedLegFrequency);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        OH_GET_REFERENCE(ShiborIndexLibObjPtr, ShiborIndex,
            QuantLibAddin::Shibor, QuantLib::Shibor)

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALShiborSwapRateHelper(
                ObjectId,
                Rate,
                SwapTenor,
                FixedLegFrequency,
                ShiborIndex,
                ForwardStart,
                DiscountingCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ShiborSwapRateHelper(
                valueObject,
                RateLibObj,
                SwapTenorLib,
                FixedLegFrequencyEnum,
                ShiborIndexLibObjPtr,
                ForwardStartLib,
                DiscountingCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALShiborSwapRateHelper : " << e.what());
        }
    }


    std::string CALSwapRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &SwapIndex,
            const ObjectHandler::property_t &Spread,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &DiscountingCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DiscountingCurveCpp = ObjectHandler::convert2<std::string>(
            DiscountingCurve, "DiscountingCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALSwapRateHelper(
                ObjectId,
                Rate,
                SwapIndex,
                Spread,
                ForwardStart,
                DiscountingCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwapRateHelper(
                valueObject,
                RateLibObj,
                SwapIndexLibObjPtr,
                SpreadLibObj,
                ForwardStartLib,
                DiscountingCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALSwapRateHelper : " << e.what());
        }
    }


    std::string CALSwapRateHelper2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &Tenor,
            const std::string &Calendar,
            const std::string &FixedLegFrequency,
            const std::string &FixedLegConvention,
            const std::string &FixedLegDayCounter,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Spread,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &DiscountingCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DiscountingCurveCpp = ObjectHandler::convert2<std::string>(
            DiscountingCurve, "DiscountingCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::Frequency FixedLegFrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FixedLegFrequency);

        QuantLib::BusinessDayConvention FixedLegConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(FixedLegConvention);

        QuantLib::DayCounter FixedLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixedLegDayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALSwapRateHelper2(
                ObjectId,
                Rate,
                Tenor,
                Calendar,
                FixedLegFrequency,
                FixedLegConvention,
                FixedLegDayCounter,
                IborIndex,
                Spread,
                ForwardStart,
                DiscountingCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwapRateHelper(
                valueObject,
                RateLibObj,
                TenorLib,
                CalendarEnum,
                FixedLegFrequencyEnum,
                FixedLegConventionEnum,
                FixedLegDayCounterEnum,
                IborIndexLibObjPtr,
                SpreadLibObj,
                ForwardStartLib,
                DiscountingCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALSwapRateHelper2 : " << e.what());
        }
    }

}

