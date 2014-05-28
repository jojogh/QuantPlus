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

/*! \file amortizingfixedratebond.hpp
    \brief amortizing fixed-rate bond
*/

#ifndef quantlib_amortizing_fixed_rate_bond_hpp
#define quantlib_amortizing_fixed_rate_bond_hpp

#include <ql/instruments/bond.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/time/calendars/nullcalendar.hpp>

namespace QuantLib {

    class Schedule;

    //! amortizing fixed-rate bond
    class AmortizingFixedRateBond : public Bond {
      public:
		enum AmortizingType {
			EqualPayment,
			EqualPrinciple
		};

		/*! Exactly same with fixed rate coupon with variable coupons and notionals.
		*/

        AmortizingFixedRateBond(
                          Natural settlementDays,
                          const std::vector<Real>& notionals,
                          const Schedule& schedule,
                          const std::vector<Rate>& coupons,
                          const DayCounter& accrualDayCounter,
						  const Calendar& paymentCalendar = NullCalendar(),
                          BusinessDayConvention paymentConvention = Following,
                          const Date& issueDate = Date());
        /*! Automatically generates a set of equal coupons, with an
            amortizing bond.  The coupons are equal and the accrual
            daycount is only used for quoting/settlement purposes -
            not for calculating the coupons.
        */
        AmortizingFixedRateBond(
                          Natural settlementDays,
                          const Calendar& calendar,
                          Real faceAmount,
                          const Date& startDate,
                          const Period& bondTenor,
                          const Frequency& sinkingFrequency,
                          const Rate coupon,
                          const DayCounter& accrualDayCounter,
						  const Calendar& paymentCalendar = NullCalendar(),
                          BusinessDayConvention paymentConvention = Following,
						  AmortizingType type = EqualPayment,
                          const Date& issueDate = Date());

		/*! Automatically generates a set of cash flows which make equal pay down
			on the principle.
		*/
		AmortizingFixedRateBond(
			Natural settlementDays,
			const Calendar& calendar,
			Real startAmount,
			Real endAmount,
			const Date& startDate,
			const Period& bondTenor,
			const Frequency& sinkingFrequency,
			const Rate& coupon,
			const DayCounter& accrualDayCounter,
			const Calendar& paymentCalendar = NullCalendar(),
			BusinessDayConvention paymentConvention = Following,
			AmortizingType type = EqualPayment,
			const Date& issueDate = Date());

        Frequency frequency() const { return frequency_; }
        const DayCounter& dayCounter() const { return dayCounter_; }
      protected:
        Frequency frequency_;
        DayCounter dayCounter_;
    };

	/*
	  Loan type which is derived from AmortizingFixedRate bond.
	  This loan type is for ABS structuring purpose 
	*/
	class AmortizingFixedRateLoan
		: public AmortizingFixedRateBond {
	public:
		AmortizingFixedRateLoan(
			Natural settlementDays,
			const Calendar& calendar,
			Real faceAmount,
			const Date& startDate,
			const Period& loanTenor,
			const Frequency& sinkingFrequency,
			const Rate& coupon,
			const DayCounter& accrualDayCounter,
			const Calendar& paymentCalendar = NullCalendar(),
			BusinessDayConvention paymentConvention = Following,
			AmortizingType type = EqualPayment);
	};

}

#endif
