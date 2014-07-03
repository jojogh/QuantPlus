/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) Cheng Li, DataYes

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

/*! \file repocompoundingswap.hpp
    \brief fixed-rate vs compounded repo swap
*/

#ifndef quantlib_repo_compounding_swap_hpp
#define quantlib_repo_compounding_swap_hpp

#include <ql/instruments/swap.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/time/schedule.hpp>
#include <boost/optional.hpp>

namespace QuantLib {

	class RepoChina;
	class IborIndex;

	class RepoCompoundingSwap : public Swap {
		
	public:
		enum Type { Receiver = -1, Payer = 1 };
		RepoCompoundingSwap(
			Type type,
			Real nominal,
			const Schedule& fixedSchedule,
			Rate fixedRate,
			const DayCounter& fixedDayCount,
			const Schedule& floatSchedule,
			const boost::shared_ptr<RepoChina>& iborIndex,
			Spread rateSpread,
			Spread couponSpread,
			const DayCounter& floatingDayCount,
			boost::optional<BusinessDayConvention> paymentConvention =
			boost::none);

		Type type() const;
		Real nominal() const;

		Real fixedLegBPS() const;
		Real fixedLegNPV() const;
		Rate fairRate() const;

		Real floatingLegBPS() const;
		Real floatingLegNPV() const;
		Spread fairRateSpread() const;

		const Schedule& fixedSchedule() const;
        Rate fixedRate() const;
        const DayCounter& fixedDayCount() const;

        const Schedule& floatingSchedule() const;
        const boost::shared_ptr<IborIndex>& iborIndex() const;
        Spread rateSpread() const;
        const DayCounter& floatingDayCount() const;

        BusinessDayConvention paymentConvention() const;

        const Leg& fixedLeg() const;
        const Leg& floatingLeg() const;

		void fetchResults(const PricingEngine::results* r) const;

	private:
		Type type_;
		Real nominal_;
		Schedule fixedSchedule_;
		Rate fixedRate_;
		DayCounter fixedDayCount_;
		Schedule floatingSchedule_;
		boost::shared_ptr<IborIndex> iborIndex_;
		Spread rateSpread_;
		Spread couponSpread_;
		DayCounter floatingDayCount_;
		BusinessDayConvention paymentConvention_;
		// results
		mutable Rate fairRate_;
		mutable Spread fairRateSpread_;

	};

	class IBFRSwap : public RepoCompoundingSwap {

	public:
		IBFRSwap(Type type,
			      Real nominal,
				  Date startDate,
				  Period swapTenor,
				  Period paymentTenor,
				  Rate fixedRate,
				  Rate rateSpread,
				  const boost::shared_ptr<RepoChina>& iborIndex);

	};

	inline RepoCompoundingSwap::Type RepoCompoundingSwap::type() const {
		return type_;
	}

	inline Real RepoCompoundingSwap::nominal() const {
		return nominal_;
	}

	inline const Schedule& RepoCompoundingSwap::fixedSchedule() const {
        return fixedSchedule_;
    }

    inline Rate RepoCompoundingSwap::fixedRate() const {
        return fixedRate_;
    }

    inline const DayCounter& RepoCompoundingSwap::fixedDayCount() const {
        return fixedDayCount_;
    }

    inline const Schedule& RepoCompoundingSwap::floatingSchedule() const {
        return floatingSchedule_;
    }

    inline const boost::shared_ptr<IborIndex>& RepoCompoundingSwap::iborIndex() const {
        return iborIndex_;
    }

    inline Spread RepoCompoundingSwap::rateSpread() const {
        return rateSpread_;
    }

    inline const DayCounter& RepoCompoundingSwap::floatingDayCount() const {
        return floatingDayCount_;
    }

    inline BusinessDayConvention RepoCompoundingSwap::paymentConvention() const {
        return paymentConvention_;
    }

    inline const Leg& RepoCompoundingSwap::fixedLeg() const {
        return legs_[0];
    }

    inline const Leg& RepoCompoundingSwap::floatingLeg() const {
        return legs_[1];
    }

}

#endif