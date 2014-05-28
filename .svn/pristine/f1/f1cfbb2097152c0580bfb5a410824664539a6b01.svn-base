/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2013 Cheng Li, DataYes

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

/*! \file libor.cpp
    \brief base class for China Shibor indexes
*/

#include <ql/indexes/ibor/shibor.h>
#include <ql/time/calendars/jointcalendar.hpp>
#include <ql/currencies/asia.hpp>
#include <ql/time/calendars/china.hpp>
#include <ql/time/daycounters/actual360.hpp>

namespace QuantLib {

	namespace {

		BusinessDayConvention shiborConvention(const Period& p) {
			switch (p.units()) {
			case Days:
			case Weeks:
				return Following;
			case Months:
			case Years:
				return ModifiedFollowing;
			default:
				QL_FAIL("invalid time units");
			}
		}

		bool shiborEOM(const Period& p) {
			switch (p.units()) {
			case Days:
			case Weeks:
				return false;
			case Months:
			case Years:
				return true;
			default:
				QL_FAIL("invalid time units");
			}
		}
	}

		Shibor::Shibor(
			const Period& tenor,
			const Handle<YieldTermStructure>& h) 
			: IborIndex("shibor", tenor, (tenor.units()==Days && tenor.length()==1)? 0:1, CNYCurrency(),
			China(China::IB),
			shiborConvention(tenor), shiborEOM(tenor),
			Actual360(), h),
			financialCenterCalendar_(China(China::IB)),
			jointCalendar_(JointCalendar(China(China::IB),
			China(China::IB),
			JoinHolidays)) {

		}

		Date Shibor::valueDate(const Date& fixingDate) const {

			QL_REQUIRE(isValidFixingDate(fixingDate),
				"Fixing date " << fixingDate << " is not valid");

			Date d = fixingCalendar().advance(fixingDate, fixingDays_, Days);
			return jointCalendar_.adjust(d);
		}

		Date Shibor::maturityDate(const Date& valueDate) const {
			return jointCalendar_.advance(valueDate, tenor_, convention_,
				endOfMonth());
		}

		Calendar Shibor::jointCalendar() const {
			return jointCalendar_;
		}

		boost::shared_ptr<IborIndex> Shibor::clone(
			const Handle<YieldTermStructure>& h) const {
				return boost::shared_ptr<IborIndex>(new Shibor(
					tenor(),
					h));
		}

}