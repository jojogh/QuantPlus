/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Aurelien Chanudet
 Copyright (C) 2011 Ferdinando Ametrano
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

#ifndef qla_simpleswap_hpp
#define qla_simpleswap_hpp

#include <qlo/swap.hpp>

#include <ql/instruments/vanillaswap.hpp>
#include <ql/instruments/shiborswap.h>
#include <ql/instruments/repocompoundingswap.h>

namespace QuantLib {
    class SwapRateHelper;
}

namespace QuantLibAddin {

    class VanillaSwap : public Swap {
    public:
        VanillaSwap(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::VanillaSwap::Type type,
            QuantLib::Real nominal,
            const boost::shared_ptr<QuantLib::Schedule>& fixedSchedule,
            QuantLib::Rate fixedRate,
            const QuantLib::DayCounter& fixLegDayCounter,
            const boost::shared_ptr<QuantLib::Schedule>& floatSchedule,
            const boost::shared_ptr<QuantLib::IborIndex>& iborIndex,
            QuantLib::Spread floatingLegSpread,
            const QuantLib::DayCounter& floatDayCounter,
            QuantLib::BusinessDayConvention paymentConvention,
            bool permanent);
        VanillaSwap( // MakeVanillaSwap
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Period& swapTenor, 
            const boost::shared_ptr<QuantLib::IborIndex>& iborIndex,
            QuantLib::Rate fixedRate,
            const QuantLib::Period& forwardStart,
            const QuantLib::DayCounter& fixLegDayCounter,
            QuantLib::Spread floatingLegSpread,
            const boost::shared_ptr<QuantLib::PricingEngine>& engine,
            bool permanent);
        VanillaSwap( // MakeIMMSwap
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Period& swapTenor, 
            const boost::shared_ptr<QuantLib::IborIndex>& iborIndex,
            QuantLib::Rate fixedRate,
            const QuantLib::Date& immDate,
            const QuantLib::DayCounter& fixLegDayCounter,
            QuantLib::Spread floatingLegSpread,
            const boost::shared_ptr<QuantLib::PricingEngine>& engine,
            bool permanent);
        VanillaSwap( // SwapIndex->underlyingSwap()
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::SwapIndex>& swapIndex,
            const QuantLib::Date& fixingDate,
            bool permanent);
        VanillaSwap( // SwapRateHelper->swap()
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::SwapRateHelper>& swapRH,
            bool permanent);
        std::vector<std::vector<ObjectHandler::property_t> >
                                    fixedLegAnalysis(const QuantLib::Date& d);
        std::vector<std::vector<ObjectHandler::property_t> >
                                    floatingLegAnalysis(const QuantLib::Date&);

	protected:
		VanillaSwap(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
				    bool permanent)
		:Swap(properties, permanent) {}
    };

	class ShiborSwap : public VanillaSwap {
	public:
		ShiborSwap(const boost::shared_ptr<ObjectHandler::ValueObject>& properties, 
			QuantLib::VanillaSwap::Type type,
			QuantLib::Real nominal,
			QuantLib::Date startDate, 
			const QuantLib::Period& swapTenor,
			const QuantLib::Period& fixedTenor,
			QuantLib::Real fixedRate,
			const QuantLib::Period& floatTenor,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& h,
			bool permanent);

		std::vector<std::vector<ObjectHandler::property_t> >
			fixedLegAnalysis(const QuantLib::Date& d);
		std::vector<std::vector<ObjectHandler::property_t> >
			floatingLegAnalysis(const QuantLib::Date&);

	};

	class IBFRSwap : public VanillaSwap {
	public:
		IBFRSwap(const boost::shared_ptr<ObjectHandler::ValueObject>& properties, 
			QuantLib::RepoCompoundingSwap::Type type,
			QuantLib::Real nominal,
			QuantLib::Date startDate,
			QuantLib::Period swapTenor,
			QuantLib::Period paymentTenor,
			QuantLib::Rate fixedRate,
			QuantLib::Rate rateSpread,
			const boost::shared_ptr<QuantLib::RepoChina>& iborIndex,
			bool permanent);

		std::vector<std::vector<ObjectHandler::property_t> >
			fixedLegAnalysis(const QuantLib::Date& d);
		std::vector<std::vector<ObjectHandler::property_t> >
			floatingLegAnalysis(const QuantLib::Date&);

	};

}

#endif
