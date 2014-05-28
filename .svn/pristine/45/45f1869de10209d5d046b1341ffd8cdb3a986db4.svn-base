
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
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/options.hpp>
#include <qlo/payoffs.hpp>
#include <qlo/exercise.hpp>
#include <ql/instruments/oneassetoption.hpp>
#include <qlo/valueobjects/vo_options.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

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
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Barrier::Type BarrierTypeEnum =
            ObjectHandler::Create<QuantLib::Barrier::Type>()(BarrierType);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALBarrierOption(
                ObjectId,
                BarrierType,
                Barrier,
                Rebate,
                Payoff,
                Exercise,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BarrierOption(
                valueObject,
                BarrierTypeEnum,
                Barrier,
                Rebate,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALBarrierOption : " << e.what());
        }
    }


    std::string CALCaAsianOption(
            const std::string &ObjectId,
            const std::string &AverageType,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Average::Type AverageTypeEnum =
            ObjectHandler::Create<QuantLib::Average::Type>()(AverageType);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALCaAsianOption(
                ObjectId,
                AverageType,
                Payoff,
                Exercise,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ContinuousAveragingAsianOption(
                valueObject,
                AverageTypeEnum,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALCaAsianOption : " << e.what());
        }
    }


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
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size PastFixingsLib;
        QuantLibAddin::cppToLibrary(PastFixings, PastFixingsLib);

        std::vector<QuantLib::Date> FixingDatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(FixingDates, "FixingDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Average::Type AverageTypeEnum =
            ObjectHandler::Create<QuantLib::Average::Type>()(AverageType);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALDaAsianOption(
                ObjectId,
                AverageType,
                RunningAccumulator,
                PastFixings,
                FixingDates,
                Payoff,
                Exercise,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DiscreteAveragingAsianOption(
                valueObject,
                AverageTypeEnum,
                RunningAccumulator,
                PastFixingsLib,
                FixingDatesLib,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALDaAsianOption : " << e.what());
        }
    }


    std::string CALDividendVanillaOption(
            const std::string &ObjectId,
            const std::string &Payoff,
            const std::string &Exercise,
            const std::vector<ObjectHandler::property_t>& DividendDates,
            const std::vector<double>& Dividends,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DividendDatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(DividendDates, "DividendDates");

        std::vector<QuantLib::Real> DividendsLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(Dividends);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALDividendVanillaOption(
                ObjectId,
                Payoff,
                Exercise,
                DividendDates,
                Dividends,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DividendVanillaOption(
                valueObject,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                DividendDatesLib,
                DividendsLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALDividendVanillaOption : " << e.what());
        }
    }


    std::string CALEuropeanOption(
            const std::string &ObjectId,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALEuropeanOption(
                ObjectId,
                Payoff,
                Exercise,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EuropeanOption(
                valueObject,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALEuropeanOption : " << e.what());
        }
    }


    std::string CALForwardVanillaOption(
            const std::string &ObjectId,
            const double &Moneyness,
            const ObjectHandler::property_t &ResetDate,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ResetDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ResetDate, "ResetDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALForwardVanillaOption(
                ObjectId,
                Moneyness,
                ResetDate,
                Payoff,
                Exercise,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardVanillaOption(
                valueObject,
                Moneyness,
                ResetDateLib,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALForwardVanillaOption : " << e.what());
        }
    }


    std::string CALQuantoForwardVanillaOption(
            const std::string &ObjectId,
            const double &Moneyness,
            const ObjectHandler::property_t &ResetDate,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ResetDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ResetDate, "ResetDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALQuantoForwardVanillaOption(
                ObjectId,
                Moneyness,
                ResetDate,
                Payoff,
                Exercise,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::QuantoForwardVanillaOption(
                valueObject,
                Moneyness,
                ResetDateLib,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALQuantoForwardVanillaOption : " << e.what());
        }
    }


    std::string CALQuantoVanillaOption(
            const std::string &ObjectId,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALQuantoVanillaOption(
                ObjectId,
                Payoff,
                Exercise,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::QuantoVanillaOption(
                valueObject,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALQuantoVanillaOption : " << e.what());
        }
    }


    std::string CALVanillaOption(
            const std::string &ObjectId,
            const std::string &Payoff,
            const std::string &Exercise,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::CALVanillaOption(
                ObjectId,
                Payoff,
                Exercise,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaOption(
                valueObject,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function CALVanillaOption : " << e.what());
        }
    }

}

