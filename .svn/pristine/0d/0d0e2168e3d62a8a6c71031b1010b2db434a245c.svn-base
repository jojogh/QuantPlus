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

/*! \file subperiodcoupons.hpp
    \brief averaging coupons
*/

#ifndef quantlib_sub_period_coupons_hpp
#define quantlib_sub_period_coupons_hpp

#include <ql/cashflows/couponpricer.hpp>
#include <ql/cashflows/floatingratecoupon.hpp>
#include <ql/time/businessdayconvention.hpp>
#include <ql/time/schedule.hpp>
#include <vector>

namespace QuantLib {

    class IborIndex;
    class AveragingRatePricer;
	class Calendar;

    class SubPeriodsCoupon: public FloatingRateCoupon {
      public:
          // The index object passed in has a tenor significantly less than the
          // start/end dates.
          // Thus endDate-startDate may equal 3M
          // The Tenor used within the index object should be 1M for
          // averaging/compounding across three coupons within the
          // coupon period.
          SubPeriodsCoupon(
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
                Rate couponSpread, // Spread added to the computed
                                   // averaging/compounding rate.
                Rate rateSpread, // Spread to be added onto each
                                 // fixing within the
                                 // averaging/compounding calculation
                const Date& refPeriodStart,
                const Date& refPeriodEnd);

        Spread rateSpread() const { return rateSpread_; }

        Size observations() const { return observations_; }
        const std::vector<Date>& observationDates() const {
            return observationDates_;
        }

        const boost::shared_ptr<Schedule> observationsSchedule() const {
            return observationsSchedule_;
        }

		const Date& lastEndValueDate() const {return lastEndValueDate_;}

        Real priceWithoutOptionality(
                       const Handle<YieldTermStructure>& discountCurve) const;
        //! \name Visitability
        //@{
        virtual void accept(AcyclicVisitor&);
        //@}
      private:                               // T
        boost::shared_ptr<Schedule> observationsSchedule_;
        std::vector<Date> observationDates_;

        Size observations_;
        Rate rateSpread_;

		Date lastEndValueDate_;
    };

    class SubPeriodsPricer: public FloatingRateCouponPricer {
      public:
        virtual Rate swapletRate() const;
        virtual Real capletPrice(Rate effectiveCap) const;
        virtual Rate capletRate(Rate effectiveCap) const;
        virtual Real floorletPrice(Rate effectiveFloor) const;
        virtual Rate floorletRate(Rate effectiveFloor) const;
        void initialize(const FloatingRateCoupon& coupon);

      protected:
        const SubPeriodsCoupon* coupon_;
        Real startTime_;
        Real endTime_;
        Real accrualFactor_;
        std::vector<Real> observationTimes_;
        std::vector<Real> observationCvg_;
        std::vector<Real> initialValues_;

        std::vector<Date> observationIndexStartDates_;
        std::vector<Date> observationIndexEndDates_;

        Size observations_;
        Real discount_;
        Real gearing_;
        Spread spread_;
        Real spreadLegValue_;

    };

	class SubPeriodsCouponLeg {
	public:
		SubPeriodsCouponLeg(const Schedule& schedule,
			const boost::shared_ptr<IborIndex>& index);
		SubPeriodsCouponLeg& withNotionals(Real notional);
		SubPeriodsCouponLeg& withNotionals(const std::vector<Real>& notionals);
		SubPeriodsCouponLeg& withPaymentDayCounter(const DayCounter&);
		SubPeriodsCouponLeg& withPaymentAdjustment(BusinessDayConvention);
		SubPeriodsCouponLeg& withFixingDays(Natural fixingDays);
		SubPeriodsCouponLeg& withFixingDays(const std::vector<Natural>& fixingDays);
		SubPeriodsCouponLeg& withGearings(Real gearing);
		SubPeriodsCouponLeg& withGearings(const std::vector<Real>& gearings);
		SubPeriodsCouponLeg& withRateSpreads(Spread spread);
		SubPeriodsCouponLeg& withRateSpreads(const std::vector<Spread>& spreads);
		SubPeriodsCouponLeg& withCouponSpreads(Spread spread);
		SubPeriodsCouponLeg& withCouponSpreads(const std::vector<Spread>& spreads);
		SubPeriodsCouponLeg& withZeroPayments(bool flag = true);
		operator Leg() const;
	private:
		Schedule schedule_;
		boost::shared_ptr<IborIndex> index_;
		std::vector<Real> notionals_;
		DayCounter paymentDayCounter_;
		BusinessDayConvention paymentAdjustment_;
		std::vector<Natural> fixingDays_;
		std::vector<Real> gearings_;
		std::vector<Spread> rateSpreads_;
		std::vector<Spread> couponSpreads_;
		bool zeroPayments_;
	};

    class AveragingRatePricer: public SubPeriodsPricer {
      public:
        Real swapletPrice() const;
    };

    class CompoundingRatePricer: public SubPeriodsPricer {
      public:
        Real swapletPrice() const;
    };

	class SimpleCompoundingRatePricer : public SubPeriodsPricer {
	public:
		Real swapletPrice() const;
	};

}


#endif
