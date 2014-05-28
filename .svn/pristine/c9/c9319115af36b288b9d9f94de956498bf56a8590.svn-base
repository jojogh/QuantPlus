/*

	Copyright (C) Cheng Li, DataYes, 2013

	Concrete class for China fixed rate bond;

	DCF: Actual/Actual (NO LEAP)
	BDC: Unadjusted (to be discussed)
	Compounding: Simple (in last periof)
			     Compounded (otherwise)

*/

#ifndef cal_ctb_fixed_bond_hpp
#define cal_ctb_fixed_bond_hpp

#include <ql/instruments/bonds/fixedratebond.hpp>
#include <ql/time/dategenerationrule.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/time/daycounters/actualactualnl.h>
#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/interestrate.hpp>

namespace QuantLib {

	class CTBFixedBond
		: public FixedRateBond {
	public:

		CTBFixedBond(const Date& issueDate,
				Natural settlementDays,
				Real faceAmount,
				const Date& startDate,
				const Date& maturity,
				const Period& tenor,			   
				const std::vector<Rate>& coupons,
				const DayCounter& accrualDayCounter = ActualActualNoLeap(),
				bool endOfMonth = false,
				const Calendar& calendar = NullCalendar(),
				const Calendar& paymentCalendar = China(),
				BusinessDayConvention convention = Unadjusted,
				DateGeneration::Rule rule = DateGeneration::Backward,
				BusinessDayConvention paymentConvention = Unadjusted,
				Real redemption = 100.0,
				const Date& firstDate = Date(),
				const Date& nextToLastDate = Date());

	};

}

#endif