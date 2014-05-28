
/*  
 Copyright (C) 2007 Ferdinando Ametrano
 Copyright (C) 2005, 2006 Eric Ehlers
 
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

#ifndef qlcpp_options_hpp
#define qlcpp_options_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string CALBarrierOption(
            const std::string &ObjectId,
            const std::string &BarrierType,
            const double &Barrier,
            const double &Rebate,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALCaAsianOption(
            const std::string &ObjectId,
            const std::string &AverageType,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALDaAsianOption(
            const std::string &ObjectId,
            const std::string &AverageType,
            const double &RunningAccumulator,
            const long &PastFixings,
            const std::vector<ObjectHandler::property_t>& FixingDates,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALDividendVanillaOption(
            const std::string &ObjectId,
            const std::string &Payoff,
            const std::string &Exercise,
            const std::vector<ObjectHandler::property_t>& DividendDates,
            const std::vector<double>& Dividends,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALEuropeanOption(
            const std::string &ObjectId,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALForwardVanillaOption(
            const std::string &ObjectId,
            const double &Moneyness,
            const ObjectHandler::property_t &ResetDate,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALQuantoForwardVanillaOption(
            const std::string &ObjectId,
            const double &Moneyness,
            const ObjectHandler::property_t &ResetDate,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALQuantoVanillaOption(
            const std::string &ObjectId,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALVanillaOption(
            const std::string &ObjectId,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

