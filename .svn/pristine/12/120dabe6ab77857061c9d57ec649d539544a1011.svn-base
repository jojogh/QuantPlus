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

/*! \file repochina.cpp
    \brief base class for China Shibor indexes
*/

#include <ql/indexes/ibor/repochina.h>
#include <ql/time/calendars/jointcalendar.hpp>
#include <ql/currencies/asia.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>
#include <ql/time/calendars/china.hpp>

namespace QuantLib {

	namespace {

		BusinessDayConvention repoChinaConvention(const Period& p) {
			switch (p.units()) {
			case Days:
			case Weeks:
			case Months:
			case Years:
				return Following;
			default:
				QL_FAIL("invalid time units. Only days can be used for china repor index.");
			}
		}

		bool repoChinaEOM(const Period& p) {
			switch (p.units()) {
			case Days:
			case Weeks:
			case Months:
			case Years:
				return false;
			default:
				QL_FAIL("invalid time units. Only days can be used for china repor index.");
			}
		}
	}

		RepoChina::RepoChina(
			const Period& tenor,
			const Handle<YieldTermStructure>& h) 
			: IborIndex("repoChina", tenor, (tenor.length()==1 && tenor.units()==Days)? 0:1, CNYCurrency(),
			China(China::IB),
			repoChinaConvention(tenor), repoChinaEOM(tenor),
			Actual365Fixed(), h),
			financialCenterCalendar_(China(China::IB)),
			jointCalendar_(JointCalendar(China(China::IB),
			China(China::IB),
			JoinHolidays)) {

		}

		Date RepoChina::valueDate(const Date& fixingDate) const {

			QL_REQUIRE(isValidFixingDate(fixingDate),
				"Fixing date " << fixingDate << " is not valid");

			Date d = fixingCalendar().advance(fixingDate, fixingDays_, Days);
			return jointCalendar_.adjust(d);
		}

		Date RepoChina::maturityDate(const Date& valueDate) const {
			return jointCalendar_.advance(valueDate, tenor_, convention_,
				endOfMonth());
		}

		Calendar RepoChina::jointCalendar() const {
			return jointCalendar_;
		}

		boost::shared_ptr<IborIndex> RepoChina::clone(
			const Handle<YieldTermStructure>& h) const {
				return boost::shared_ptr<IborIndex>(new RepoChina(
					tenor(),
					h));
		}

}