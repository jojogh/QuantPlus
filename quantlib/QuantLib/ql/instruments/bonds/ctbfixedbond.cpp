/*

	Copyright (C) Cheng Li, DataYes, 2013

	Concrete class for China fixed rate bond;

	DCF: Actual/Actual (NO LEAP)
	BDC: Unadjusted (to be discussed)
	Compounding: Simple (in last periof)
			     Compounded (otherwise)

*/

#include <ql/instruments/bonds/ctbfixedbond.h>
#include <ql/time/schedule.hpp>

namespace QuantLib {

	CTBFixedBond::CTBFixedBond(const Date& issueDate, 
							   Natural settlementDays, 
							   Real faceAmount, 
							   const Date& startDate, 
							   const Date& maturity, 
							   const Period& tenor, 
							   const std::vector<Rate>& coupons, 
							   const DayCounter& accrualDayCounter,
							   bool endOfMonth,
							   const Calendar& calendar,
							   const Calendar& paymentCalendar,
							   BusinessDayConvention convention,
							   DateGeneration::Rule rule,
							   BusinessDayConvention paymentConvention,
							   Real redemption,
							   const Date& firstDate,
							   const Date& nextToLastDate)
				:FixedRateBond(settlementDays,
							   faceAmount,
					  Schedule(startDate,
							   maturity,
							   tenor,
							   calendar,
							   convention,
							   convention,
							   rule,
							   endOfMonth,
							   firstDate,
							   nextToLastDate),
							   coupons,
							   accrualDayCounter,
							   paymentConvention,
							   redemption,
							   issueDate,
							   paymentCalendar) {

		
	}

}