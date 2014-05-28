
/*  
 Copyright (C) 2006, 2007 Chiara Fornarola
 Copyright (C) 2006, 2007, 2008, 2009, 2010, 2011 Ferdinando Ametrano
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Walter Penschke
 Copyright (C) 2009 Piter Dias
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
//      gensrc/gensrc/stubs/stub.cpp.header

#ifndef qlcpp_bonds_hpp
#define qlcpp_bonds_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string CALAmortizingFixedRateBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const std::string &Calendar,
            const ObjectHandler::property_t &FaceAmount,
            const ObjectHandler::property_t &StartDate,
            const std::string &Tenor,
            const std::string &Frequency,
            const double &Coupon,
            const ObjectHandler::property_t &DayCounter,
            const std::string &PayCalendar,
            const ObjectHandler::property_t &BDC,
            const ObjectHandler::property_t &AmortizingType,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALAmortizingFixedRateBond2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const std::string &Calendar,
            const ObjectHandler::property_t &StartAmount,
            const ObjectHandler::property_t &EndAmount,
            const ObjectHandler::property_t &StartDate,
            const std::string &Tenor,
            const std::string &Frequency,
            const double &Coupon,
            const ObjectHandler::property_t &DayCounter,
            const std::string &PayCalendar,
            const ObjectHandler::property_t &BDC,
            const ObjectHandler::property_t &AmortizingType,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const ObjectHandler::property_t &Currency,
            const ObjectHandler::property_t &SettlementDays,
            const ObjectHandler::property_t &Calendar,
            const ObjectHandler::property_t &FaceAmount,
            const ObjectHandler::property_t &MaturityDate,
            const ObjectHandler::property_t &IssueDate,
            const std::string &LegID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALCTBFixedBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const ObjectHandler::property_t &IssueDate,
            const long &SettlementDays,
            const ObjectHandler::property_t &FaceAmount,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &Maturity,
            const std::string &Tenor,
            const std::vector<double>& Coupons,
            const std::string &DayCounter,
            const ObjectHandler::property_t &EndOfMonth,
            const ObjectHandler::property_t &Calendar,
            const ObjectHandler::property_t &PaymentCalendar,
            const ObjectHandler::property_t &BDC,
            const ObjectHandler::property_t &Rule,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &FirstDate,
            const ObjectHandler::property_t &NextToLastDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALCTBZeroBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const std::string &Calendar,
            const ObjectHandler::property_t &FaceAmount,
            const ObjectHandler::property_t &IssuePrice,
            const ObjectHandler::property_t &IssueDate,
            const std::string &AccrualDayCounter,
            const ObjectHandler::property_t &Maturity,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALCallability(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PriceType,
            const double &Amount,
            const std::string &CallType,
            const ObjectHandler::property_t &CallDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALCallabilitySchedule(
            const std::string &ObjectId,
            const std::vector<std::string>& Callabilities,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALCallableFixedRateBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const ObjectHandler::property_t &Currency,
            const ObjectHandler::property_t &SettlementDays,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const std::vector<double>& Coupons,
            const std::string &AccrualDayCounter,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const std::string &PutCallSchedule,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALCmsRateBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const ObjectHandler::property_t &FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string &SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALFixedRateBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const std::vector<double>& Coupons,
            const std::string &DayCounter,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const std::string &PaymentCalendar,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALFixedRateBond2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const std::vector<std::string>& Coupons,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const std::string &PaymentCalendar,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALFloatingRateBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const ObjectHandler::property_t &FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string &IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALZeroCouponBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const std::string &Calendar,
            const ObjectHandler::property_t &FaceAmount,
            const ObjectHandler::property_t &Maturity,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

