
/*  
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
 Copyright (C) 2006, 2007 Marco Bianchetti
 Copyright (C) 2006, 2007 Cristina Duminuco
 Copyright (C) 2006, 2007 Giorgio Facchinetti
 
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

#ifndef qlcpp_marketmodels_hpp
#define qlcpp_marketmodels_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string CALAbcdVol(
            const std::string &ObjectId,
            const double &A,
            const double &B,
            const double &C,
            const double &D,
            const std::vector<double>& Ks,
            const std::string &Correlations,
            const std::string &EvolutionDescription,
            const long &Factors,
            const std::vector<double>& InitialRates,
            const std::vector<double>& Displacements,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALCotSwapToFwdAdapter(
            const std::string &ObjectId,
            const std::string &CoterminalModel,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALFlatVol(
            const std::string &ObjectId,
            const std::vector<double>& Volatilities,
            const std::string &Correlations,
            const std::string &EvolutionDescription,
            const long &Factors,
            const std::vector<double>& InitialRates,
            const std::vector<double>& Displacements,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALFlatVolFactory(
            const std::string &ObjectId,
            const double &LongTermCorr,
            const double &Beta,
            const std::vector<double>& Times,
            const std::vector<double>& Volatilities,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Displacement,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALFwdPeriodAdapter(
            const std::string &ObjectId,
            const std::string &LargeModel,
            const long &Period,
            const long &Offset,
            const std::vector<double>& Displacements,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALFwdToCotSwapAdapter(
            const std::string &ObjectId,
            const std::string &ForwardModel,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALPseudoRootFacade(
            const std::string &ObjectId,
            const std::string &Calibrator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

