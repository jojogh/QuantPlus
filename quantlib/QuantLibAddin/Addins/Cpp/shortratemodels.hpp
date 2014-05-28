
/*  
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2005 Aurelien Chanudet
 Copyright (C) 2005 Eric Ehlers
 Copyright (C) 2006 Chiara Fornarola
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

#ifndef qlcpp_shortratemodels_hpp
#define qlcpp_shortratemodels_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string CALBlackKarasinski(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const double &A,
            const double &Sigma,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALCIR(
            const std::string &ObjectId,
            const double &R0,
            const double &Theta,
            const double &K,
            const double &Sigma,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALCIRShortRate(
            const std::string &ObjectId,
            const double &R0,
            const double &Theta,
            const double &K,
            const double &Sigma,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALExtendedCIR(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const double &Theta,
            const double &K,
            const double &Sigma,
            const double &X0,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALExtendedCIRShortRate(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const double &Theta,
            const double &K,
            const double &Sigma,
            const double &X0,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALGeneralizedHullWhite(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const double &A,
            const double &Sigma,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALGeneralizedHullWhiteShortRate(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const double &A,
            const double &Sigma,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALHullWhite(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const double &A,
            const double &Sigma,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALHullWhiteShortRate(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const double &A,
            const double &Sigma,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALVasicek(
            const std::string &ObjectId,
            const double &A,
            const double &B,
            const double &Lambda,
            const double &Sigma,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string CALVasicekShortRate(
            const std::string &ObjectId,
            const double &A,
            const double &B,
            const double &Lambda,
            const double &Sigma,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif
