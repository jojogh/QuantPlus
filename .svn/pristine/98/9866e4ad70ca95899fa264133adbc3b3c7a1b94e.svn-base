/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2008 Simon Ibbotson

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

#include <ql/experimental/amortizingbonds/amortizingfixedratebond.hpp>
#include <ql/cashflows/cashflowvectors.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <ql/time/schedule.hpp>

namespace QuantLib {

    AmortizingFixedRateBond::AmortizingFixedRateBond(
                                      Natural settlementDays,
                                      const std::vector<Real>& notionals,
                                      const Schedule& schedule,
                                      const std::vector<Rate>& coupons,
                                      const DayCounter& accrualDayCounter,
									  const Calendar& paymentCalendar,
                                      BusinessDayConvention paymentConvention,
                                      const Date& issueDate)
    : Bond(settlementDays, schedule.calendar(), issueDate),
      frequency_(schedule.tenor().frequency()),
      dayCounter_(accrualDayCounter) {

        maturityDate_ = schedule.endDate();

        cashflows_ = FixedRateLeg(schedule)
            .withNotionals(notionals)
            .withCouponRates(coupons, accrualDayCounter)
			.withPaymentCalendar(paymentCalendar)
            .withPaymentAdjustment(paymentConvention);

        addRedemptionsToCashflows();

        QL_ENSURE(!cashflows().empty(), "bond with no cashflows!");
    }

    namespace  {

        std::pair<Integer,Integer> daysMinMax(const Period& p) {
            switch (p.units()) {
              case Days:
                return std::make_pair(p.length(), p.length());
              case Weeks:
                return std::make_pair(7*p.length(), 7*p.length());
              case Months:
                return std::make_pair(28*p.length(), 31*p.length());
              case Years:
                return std::make_pair(365*p.length(), 366*p.length());
              default:
                QL_FAIL("unknown time unit (" << Integer(p.units()) << ")");
            }
        }

        bool isSubPeriod(const Period& subPeriod,
                         const Period& superPeriod,
                         Integer& numSubPeriods) {

            std::pair<Integer, Integer> superDays(daysMinMax(superPeriod));
            std::pair<Integer, Integer> subDays(daysMinMax(subPeriod));

            //obtain the approximate time ratio
            Real minPeriodRatio =
                ((Real)superDays.first)/((Real)subDays.second);
            Real maxPeriodRatio =
                ((Real)superDays.second)/((Real)subDays.first);
            Integer lowRatio = static_cast<Integer>(std::floor(minPeriodRatio));
            Integer highRatio = static_cast<Integer>(std::ceil(maxPeriodRatio));

            try {
                for(Integer i=lowRatio; i <= highRatio; ++i) {
                    Period testPeriod = subPeriod * i;
                    if(testPeriod == superPeriod) {
                        numSubPeriods = i;
                        return true;
                    }
                }
            } catch(Error e) {
                return false;
            }

            return false;
        }

        Schedule sinkingSchedule(const Date& startDate,
                                 const Period& maturityTenor,
                                 const Frequency& sinkingFrequency,
                                 const Calendar& paymentCalendar) {
            Period freqPeriod(sinkingFrequency);
            Date maturityDate(startDate + maturityTenor);
            Schedule retVal(startDate, maturityDate, freqPeriod,
                            paymentCalendar, Unadjusted, Unadjusted,
                            DateGeneration::Backward, false);
            return retVal;
        }

        std::vector<Real> sinkingNotionals(const Period& maturityTenor,
                                           const Frequency& sinkingFrequency,
                                           Rate couponRate,
                                           Real initialNotional,
										   Real endNotional,
										   AmortizingFixedRateBond::AmortizingType type) {
            Period freqPeriod(sinkingFrequency);
            Integer nPeriods;
            QL_REQUIRE(isSubPeriod(freqPeriod, maturityTenor, nPeriods),
                       "Bond frequency is incompatible with the maturity tenor");
			QL_REQUIRE(nPeriods==1? (fabs(initialNotional - endNotional) < QL_EPSILON 
				       || endNotional == Null<Real>()) : true,
					   "As only 1 period for coupon, initial notional should be same with endNotional");

            std::vector<Real> notionals(nPeriods+1);
            notionals.front() = initialNotional;
           
			if(endNotional != Null<Real>())
			{
				if(type == AmortizingFixedRateBond::EqualPayment)
				{   
					Real coupon = couponRate / static_cast<Real>(sinkingFrequency);
					Real compoundedInterest = 1.0;
					Real totalValue = std::pow(1.0+coupon, nPeriods - 1);
					Real totalAmortizedNotional = initialNotional - endNotional;
					for(Size i = 0; i < (Size)nPeriods - 1; ++i) {
						compoundedInterest *= (1.0 + coupon);
						Real currentNotional =
							totalAmortizedNotional*(compoundedInterest - (compoundedInterest-1.0)/(1.0 - 1.0/totalValue));
						notionals[i+1] = currentNotional + endNotional;
					}
				} else {
					if(nPeriods > 1)
					{
						const Real amortizingAmount = (initialNotional - endNotional) / (nPeriods - 1);
						for(Size i = 0; i < (Size)nPeriods-1; ++i) {
							Real currentNotional =
								initialNotional - (i+1) * amortizingAmount;
							notionals[i+1] = currentNotional;
						}
					}
				}
			} else {
				if(type == AmortizingFixedRateBond::EqualPayment)
				{   
					Real coupon = couponRate / static_cast<Real>(sinkingFrequency);
					Real compoundedInterest = 1.0;
					Real totalValue = std::pow(1.0+coupon, nPeriods);
					Real totalAmortizedNotional = initialNotional;
					for(Size i = 0; i < (Size)nPeriods - 1; ++i) {
						compoundedInterest *= (1.0 + coupon);
						Real currentNotional =
							totalAmortizedNotional*(compoundedInterest - (compoundedInterest-1.0)/(1.0 - 1.0/totalValue));
						notionals[i+1] = currentNotional;
					}
				} else {
					if(nPeriods > 1)
					{
						const Real amortizingAmount = initialNotional / nPeriods;
						for(Size i = 0; i < (Size)nPeriods-1; ++i) {
							Real currentNotional =
								initialNotional - (i+1) * amortizingAmount;
							notionals[i+1] = currentNotional;
						}
					}
				}
			}
            notionals.back() = 0.0;
            return notionals;
        }

        //std::vector<Real> sinkingRedemptions(const Period& maturityTenor,
        //                                     const Frequency& sinkingFrequency,
        //                                     Rate couponRate,
        //                                     Real initialNotional) {

        //    std::vector<Real> notionals =
        //        sinkingNotionals(maturityTenor, sinkingFrequency,
        //                         couponRate, initialNotional);
        //    Size nPeriods = notionals.size()-1;
        //    std::vector<Real> redemptions(nPeriods);

        //    for(Size i = 0; i < nPeriods; ++i) {
        //        redemptions[i] =
        //            (notionals[i] - notionals[i+1]) / initialNotional * 100;
        //    }
        //    return redemptions;
        //}

    }

    AmortizingFixedRateBond::AmortizingFixedRateBond(
                                      Natural settlementDays,
                                      const Calendar& calendar,
                                      Real initialFaceAmount,
                                      const Date& startDate,
                                      const Period& bondTenor,
                                      const Frequency& sinkingFrequency,
                                      const Rate coupon,
                                      const DayCounter& accrualDayCounter,
									  const Calendar& paymentCalendar,
                                      BusinessDayConvention paymentConvention,
									  AmortizingType type,
                                      const Date& issueDate)
    : Bond(settlementDays, calendar, issueDate),
      frequency_(sinkingFrequency),
      dayCounter_(accrualDayCounter) {

        maturityDate_ = startDate + bondTenor;

        cashflows_ =
            FixedRateLeg(sinkingSchedule(startDate, bondTenor,
                                         sinkingFrequency, calendar))
            .withNotionals(sinkingNotionals(bondTenor,
                                            sinkingFrequency, coupon,
                                            initialFaceAmount, Null<Real>(), type))
            .withCouponRates(coupon, accrualDayCounter)
			.withPaymentCalendar(paymentCalendar)
            .withPaymentAdjustment(paymentConvention);

        addRedemptionsToCashflows();
    }

	AmortizingFixedRateBond::AmortizingFixedRateBond(
		Natural settlementDays,
		const Calendar& calendar,
		Real startAmount,
		Real endAmount,
		const Date& startDate,
		const Period& bondTenor,
		const Frequency& sinkingFrequency,
		const Rate& coupon,
		const DayCounter& accrualDayCounter,
		const Calendar& paymentCalendar,
		BusinessDayConvention paymentConvention,
		AmortizingType type,
		const Date& issueDate) 
	:Bond(settlementDays, calendar, issueDate),
	frequency_(sinkingFrequency),
	dayCounter_(accrualDayCounter)
	{
		QL_REQUIRE(startAmount >= endAmount, "AmortizingFixedRateBond's start amount should never be smaller than end amount");

		cashflows_ = FixedRateLeg(sinkingSchedule(startDate, bondTenor,
								sinkingFrequency, calendar))
								.withNotionals(sinkingNotionals(bondTenor,
								sinkingFrequency, coupon,
								startAmount,endAmount, type))
			.withCouponRates(coupon, accrualDayCounter)
			.withPaymentCalendar(paymentCalendar)
			.withPaymentAdjustment(paymentConvention);

		addRedemptionsToCashflows();

		QL_ENSURE(!cashflows().empty(), "bond with no cashflows!");
	}

	AmortizingFixedRateLoan::AmortizingFixedRateLoan(
		Natural settlementDays,
		const Calendar& calendar,
		Real faceAmount,
		const Date& startDate,
		const Period& loanTenor,
		const Frequency& sinkingFrequency,
		const Rate& coupon,
		const DayCounter& accrualDayCounter,
		const Calendar& paymentCalendar,
		BusinessDayConvention paymentConvention,
		AmortizingType type)
		: AmortizingFixedRateBond(settlementDays,
		                          calendar,
								  faceAmount,
								  startDate,
								  loanTenor,
								  sinkingFrequency,
								  coupon,
								  accrualDayCounter,
								  paymentCalendar,
								  paymentConvention,
								  type) {}
}
