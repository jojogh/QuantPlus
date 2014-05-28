/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2008 Toyin Akin

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

#include <ql/experimental/coupons/subperiodcoupons.hpp>
#include <ql/cashflows/cashflowvectors.hpp>
#include <ql/time/schedule.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/utilities/vectors.hpp>
#include <cmath>

using boost::shared_ptr;

namespace QuantLib {

    SubPeriodsCoupon::SubPeriodsCoupon(
                                    const Date& paymentDate,
                                    Real nominal,
                                    const boost::shared_ptr<IborIndex>& index,
                                    const Date& startDate,
                                    const Date& endDate,
                                    Natural fixingDays,
                                    const DayCounter& dayCounter,
									const Calendar& calendar,
									BusinessDayConvention bdc,
                                    Real gearing,
                                    Rate couponSpread,
                                    Rate rateSpread,
                                    const Date& refPeriodStart,
                                    const Date& refPeriodEnd)
    : FloatingRateCoupon(paymentDate, nominal, startDate, endDate,
                         fixingDays, index, gearing, couponSpread,
                         refPeriodStart, refPeriodEnd, dayCounter),
      rateSpread_(rateSpread) {

        observationsSchedule_ = boost::shared_ptr<Schedule>(new
            Schedule(startDate, endDate,
                     index->tenor(),
                     calendar,
                     bdc,
                     bdc,
                     DateGeneration::Forward,
                     false));

        observationDates_ = observationsSchedule_->dates();
        observationDates_.pop_back();                       //remove end date
        observations_ = observationDates_.size();

		Date fixingDate = index->fixingCalendar().advance(
			observationDates_.back(),
			-static_cast<Integer>(fixingDays),
			Days);

		Date fixingValueDate = index->valueDate(fixingDate);
		lastEndValueDate_ = index->maturityDate(fixingValueDate);

     }

    void SubPeriodsCoupon::accept(AcyclicVisitor& v) {
        Visitor<SubPeriodsCoupon>* v1 =
            dynamic_cast<Visitor<SubPeriodsCoupon>*>(&v);
        if (v1 != 0)
            v1->visit(*this);
        else
            FloatingRateCoupon::accept(v);
    }


    void SubPeriodsPricer::initialize(const FloatingRateCoupon& coupon) {
        coupon_ =  dynamic_cast<const SubPeriodsCoupon*>(&coupon);
        QL_REQUIRE(coupon_, "sub-periods coupon required");
        gearing_ = coupon_->gearing();
        spread_ = coupon_->spread();

        Date paymentDate = coupon_->date();

        boost::shared_ptr<IborIndex> index =
            boost::dynamic_pointer_cast<IborIndex>(coupon_->index());
        const Handle<YieldTermStructure>& rateCurve =
            index->forwardingTermStructure();
        discount_ = rateCurve->discount(paymentDate);
        accrualFactor_ = coupon_->accrualPeriod();
        spreadLegValue_ = spread_ * accrualFactor_* discount_;

        observations_ = coupon_->observations();

        const std::vector<Date>& observationDates =
            coupon_->observationDates();

        QL_REQUIRE(observationDates.size()==observations_,
                   "incompatible size of initialValues vector");

        initialValues_ = std::vector<Real>(observationDates.size(),0.);

        observationCvg_ = std::vector<Real>(observationDates.size(),0.);

        observationIndexStartDates_ =
            std::vector<Date>(observationDates.size());
        observationIndexEndDates_ =
            std::vector<Date>(observationDates.size());

        Calendar calendar = index->fixingCalendar();

        for(Size i=0; i<observationDates.size(); i++) {
            Date fixingDate = calendar.advance(
                                 observationDates[i],
                                 -static_cast<Integer>(coupon_->fixingDays()),
                                 Days);

            initialValues_[i] =
                index->fixing(fixingDate) + coupon_->rateSpread();

            Date fixingValueDate = index->valueDate(fixingDate);
            Date endValueDate = index->maturityDate(fixingValueDate);

            observationIndexStartDates_[i] = fixingValueDate;
            observationIndexEndDates_[i] = endValueDate;

            observationCvg_[i] =
                index->dayCounter().yearFraction(fixingValueDate, endValueDate);
        }
    }

    Real SubPeriodsPricer::swapletRate() const {
        return swapletPrice()/(accrualFactor_*discount_);
    }

    Real SubPeriodsPricer::capletPrice(Rate) const {
        QL_FAIL("SubPeriodsPricer::capletPrice not implemented");
    }

    Rate SubPeriodsPricer::capletRate(Rate) const {
        QL_FAIL("SubPeriodsPricer::capletRate not implemented");
    }

    Real SubPeriodsPricer::floorletPrice(Rate) const {
        QL_FAIL("SubPeriodsPricer::floorletPrice not implemented");
    }

    Rate SubPeriodsPricer::floorletRate(Rate) const {
        QL_FAIL("SubPeriodsPricer::floorletRate not implemented");
    }

    Real AveragingRatePricer::swapletPrice() const {
        // past or future fixing is managed in InterestRateIndex::fixing()

        Size nCount = initialValues_.size();
        double dAvgRate = 0.0, dTotalCvg = 0.0, dTotalPayment = 0.0;
        for (Size i=0; i<nCount; i++) {
            dTotalPayment += initialValues_[i] * observationCvg_[i];
            dTotalCvg += observationCvg_[i];
        }

        dAvgRate =  dTotalPayment/dTotalCvg;

        Real swapletPrice = dAvgRate*coupon_->accrualPeriod()*discount_;
        return gearing_ * swapletPrice + spreadLegValue_;
    }

    Real CompoundingRatePricer::swapletPrice() const {
        // past or future fixing is managed in InterestRateIndex::fixing()

        double dNotional = 1.0;

        Size nCount = initialValues_.size();
        double dCompRate = 0.0, dTotalCvg = 0.0, dTotalPayment = 0.0;
        for (Size i=0; i<nCount; i++) {
            dTotalPayment = initialValues_[i] * observationCvg_[i]*dNotional;
            dNotional += dTotalPayment;
            dTotalCvg += observationCvg_[i];
        }

        dCompRate = (dNotional - 1.0)/dTotalCvg;

        Real swapletPrice = dCompRate*coupon_->accrualPeriod()*discount_;
        return gearing_ * swapletPrice + spreadLegValue_;
    }

	Real SimpleCompoundingRatePricer::swapletPrice() const {

		double dNotional = 1.0;
		Size nCount = initialValues_.size();
		double dCompRate = 0.0, dTotalCvg = 0.0, dTotalPayment = 0.0;

		for (Size i=0; i<nCount; i++) {
			dNotional *= (1.0 + initialValues_[i] * observationCvg_[i]);
			dTotalCvg += observationCvg_[i];
		}

		dCompRate = (dNotional - 1.0)/dTotalCvg;

		Real swapletPrice = dCompRate*coupon_->accrualPeriod()*discount_;
		return gearing_ * swapletPrice + spreadLegValue_;
	}

	SubPeriodsCouponLeg::SubPeriodsCouponLeg(const Schedule& schedule,
		const shared_ptr<IborIndex>& index)
		: schedule_(schedule), index_(index),
		paymentAdjustment_(Following),
		zeroPayments_(false) {}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withNotionals(Real notional) {
		notionals_ = std::vector<Real>(1,notional);
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withNotionals(const std::vector<Real>& notionals) {
		notionals_ = notionals;
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withPaymentDayCounter(const DayCounter& dayCounter) {
		paymentDayCounter_ = dayCounter;
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withPaymentAdjustment(BusinessDayConvention convention) {
		paymentAdjustment_ = convention;
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withFixingDays(Natural fixingDays) {
		fixingDays_ = std::vector<Natural>(1,fixingDays);
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withFixingDays(const std::vector<Natural>& fixingDays) {
		fixingDays_ = fixingDays;
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withGearings(Real gearing) {
		gearings_ = std::vector<Real>(1,gearing);
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withGearings(const std::vector<Real>& gearings) {
		gearings_ = gearings;
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withRateSpreads(Spread spread) {
		rateSpreads_ = std::vector<Spread>(1,spread);
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withRateSpreads(const std::vector<Spread>& spreads) {
		rateSpreads_ = spreads;
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withCouponSpreads(Spread spread) {
		couponSpreads_ = std::vector<Spread>(1,spread);
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withCouponSpreads(const std::vector<Spread>& spreads) {
		couponSpreads_ = spreads;
		return *this;
	}

	SubPeriodsCouponLeg& SubPeriodsCouponLeg::withZeroPayments(bool flag) {
		zeroPayments_ = flag;
		return *this;
	}

	SubPeriodsCouponLeg::operator Leg() const {

		// Dirty implementation. Maybe move into a seperate class in the future
		Size n = schedule_.size()-1;
		QL_REQUIRE(!notionals_.empty(), "no notional given");
		QL_REQUIRE(notionals_.size() <= n,
			"too many nominals (" << notionals_.size() <<
			"), only " << n << " required");
		QL_REQUIRE(gearings_.size()<=n,
			"too many gearings (" << gearings_.size() <<
			"), only " << n << " required");
		QL_REQUIRE(rateSpreads_.size()<=n,
			"too many rate spreads (" << rateSpreads_.size() <<
			"), only " << n << " required");
		QL_REQUIRE(couponSpreads_.size()<=n,
			"too many coupon spreads (" << couponSpreads_.size() <<
			"), only " << n << " required");

		Leg leg; leg.reserve(n);

		// the following is not always correct
		Calendar calendar = schedule_.calendar();

		Date refStart, start, refEnd, end;
		Date lastPaymentDate = calendar.adjust(schedule_.date(n), paymentAdjustment_);

		for (Size i=0; i<n; ++i) {
			refStart = start = schedule_.date(i);
			refEnd   =   end = schedule_.date(i+1);
			Date paymentDate =
				zeroPayments_ ? lastPaymentDate : calendar.adjust(end, paymentAdjustment_);
			if (i==0   && !schedule_.isRegular(i+1)) {
				BusinessDayConvention bdc = schedule_.businessDayConvention();
				refStart = calendar.adjust(end - schedule_.tenor(), bdc);
			}
			if (i==n-1 && !schedule_.isRegular(i+1)) {
				BusinessDayConvention bdc = schedule_.businessDayConvention();
				refEnd = calendar.adjust(start + schedule_.tenor(), bdc);
			}
			leg.push_back(boost::shared_ptr<CashFlow>(new
					SubPeriodsCoupon(
					paymentDate,
					detail::get(notionals_, i, 1.0),
					index_,
					start, end,
					detail::get(fixingDays_, i, index_->fixingDays()),
					paymentDayCounter_,
					calendar,
					paymentAdjustment_,
					detail::get(gearings_, i, 1.0),
					detail::get(couponSpreads_, i, 1.0),
					detail::get(rateSpreads_, i, 1.0),
					refStart, refEnd)));
		}

		shared_ptr<SimpleCompoundingRatePricer> pricer(new SimpleCompoundingRatePricer);
		setCouponPricer(leg, pricer);

		return leg;
	}

}

