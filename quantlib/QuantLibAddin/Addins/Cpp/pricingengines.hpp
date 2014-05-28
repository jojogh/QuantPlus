
/*  
 Copyright (C) 2006, 2007, 2008, 2012 Ferdinando Ametrano
 Copyright (C) 2007 Eric Ehlers
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

#ifndef qlcpp_pricingengines_hpp
#define qlcpp_pricingengines_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string CALAnalyticCapFloorEngine(
            const std::string &ObjectId,
            const std::string &HandleModel,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBinomialPricingEngine(
            const std::string &ObjectId,
            const std::string &EngineID,
            const std::string &ProcessID,
            const long &TimeSteps,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBlackCalculator(
            const std::string &ObjectId,
            const std::string &OptionType,
            const double &Strike,
            const double &AtmForwardValue,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBlackCalculator2(
            const std::string &ObjectId,
            const std::string &PayoffID,
            const double &AtmForwardValue,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBlackCapFloorEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const std::string &VolTS,
            const ObjectHandler::property_t &Displacement,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBlackCapFloorEngine2(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Vol,
            const ObjectHandler::property_t &Displacement,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBlackScholesCalculator(
            const std::string &ObjectId,
            const std::string &OptionType,
            const double &Strike,
            const double &Spot,
            const ObjectHandler::property_t &Growth,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBlackScholesCalculator2(
            const std::string &ObjectId,
            const std::string &PayoffID,
            const double &Spot,
            const ObjectHandler::property_t &Growth,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBlackSwaptionEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const std::string &VolTS,
            const ObjectHandler::property_t &Displacement,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBlackSwaptionEngine2(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Vol,
            const ObjectHandler::property_t &Displacement,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALBondEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALDiscountingSwapEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &IncludeSettlDate,
            const ObjectHandler::property_t &SettlementDate,
            const ObjectHandler::property_t &NpvDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALPricingEngine(
            const std::string &ObjectId,
            const std::string &EngineID,
            const std::string &ProcessID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALTreeCallableFixedRateBondEngine(
            const std::string &ObjectId,
            const std::string &ShortRateModel,
            const long &TimeSteps,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

