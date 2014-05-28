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

#include <ql/instruments/repocompoundingswap.h>
#include <ql/experimental/coupons/subperiodcoupons.hpp>
#include <ql/instruments/vanillaswap.hpp>
#include <ql/cashflows/fixedratecoupon.hpp>
#include <ql/cashflows/cashflowvectors.hpp>
#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>
#include <ql/time/calendars/china.hpp>
#include <ql/indexes/ibor/repochina.h>

namespace QuantLib {

	RepoCompoundingSwap::RepoCompoundingSwap(
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
		boost::optional<BusinessDayConvention> paymentConvention)
		: Swap(2), type_(type), nominal_(nominal),
		fixedSchedule_(fixedSchedule), fixedRate_(fixedRate),
		fixedDayCount_(fixedDayCount),
		floatingSchedule_(floatSchedule), iborIndex_(iborIndex), rateSpread_(rateSpread), couponSpread_(couponSpread),
		floatingDayCount_(floatingDayCount) {

			if (paymentConvention)
				paymentConvention_ = *paymentConvention;
			else
				paymentConvention_ = floatingSchedule_.businessDayConvention();

			legs_[0] = FixedRateLeg(fixedSchedule_)
				.withNotionals(nominal_)
				.withCouponRates(fixedRate_, fixedDayCount_)
				.withPaymentAdjustment(paymentConvention_);

			legs_[1] = SubPeriodsCouponLeg(floatingSchedule_, iborIndex_)
				.withNotionals(nominal_)
				.withPaymentDayCounter(floatingDayCount_)
				.withPaymentAdjustment(paymentConvention_)
				.withRateSpreads(rateSpread_)
				.withCouponSpreads(couponSpread_);
			for (Leg::const_iterator i = legs_[1].begin(); i < legs_[1].end(); ++i)
				registerWith(*i);

			switch (type_) {
			case Payer:
				payer_[0] = -1.0;
				payer_[1] = +1.0;
				break;
			case Receiver:
				payer_[0] = +1.0;
				payer_[1] = -1.0;
				break;
			default:
				QL_FAIL("Unknown repo-compounding-swap type");
			}
	}

	Rate RepoCompoundingSwap::fairRate() const {
		calculate();
		QL_REQUIRE(fairRate_ != Null<Rate>(), "result not available");
		return fairRate_;
	}

	Spread RepoCompoundingSwap::fairRateSpread() const {
		calculate();
		QL_REQUIRE(fairRateSpread_ != Null<Spread>(), "result not available");
		return fairRateSpread_;
	}

	Real RepoCompoundingSwap::fixedLegBPS() const {
		calculate();
		QL_REQUIRE(legBPS_[0] != Null<Real>(), "result not available");
		return legBPS_[0];
	}

	Real RepoCompoundingSwap::floatingLegBPS() const {
		calculate();
		QL_REQUIRE(legBPS_[1] != Null<Real>(), "result not available");
		return legBPS_[1];
	}

	Real RepoCompoundingSwap::fixedLegNPV() const {
		calculate();
		QL_REQUIRE(legNPV_[0] != Null<Real>(), "result not available");
		return legNPV_[0];
	}

	Real RepoCompoundingSwap::floatingLegNPV() const {
		calculate();
		QL_REQUIRE(legNPV_[1] != Null<Real>(), "result not available");
		return legNPV_[1];
	}

	void RepoCompoundingSwap::fetchResults(const PricingEngine::results* r) const {
		static const Spread basisPoint = 1.0e-4;

		Swap::fetchResults(r);
		fairRate_ = fixedRate_ - NPV_/(legBPS_[0]/basisPoint);

		// This implementation is not accurate enough
		fairRateSpread_ = rateSpread_ - NPV_/(legBPS_[1]/basisPoint);
	}

	IBFRSwap::IBFRSwap(Type type,
					   Real nominal,
		               Date startDate,
		               Period swapTenor,
		               Period paymentTenor,
		               Rate fixedRate,
					   Rate rateSpread,
					   const boost::shared_ptr<RepoChina>& iborIndex)
					   :RepoCompoundingSwap(type, nominal,
					   Schedule(startDate, startDate + swapTenor, paymentTenor, China(), ModifiedFollowing, ModifiedFollowing, DateGeneration::Backward, false),
					   fixedRate,
					   Actual365Fixed(),
					   Schedule(startDate, startDate + swapTenor, paymentTenor, China(), ModifiedFollowing, ModifiedFollowing, DateGeneration::Backward, false),
					   iborIndex,
					   rateSpread,
					   0.0,
					   Actual360(),
					   Following) {}

}