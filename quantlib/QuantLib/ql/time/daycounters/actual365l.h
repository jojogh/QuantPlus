/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2013 Cheng Li
 Copyright (C) 2004 Ferdinando Ametrano
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl

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

/*! \file actual365l.hpp
    \brief Actual/365 (Less) day counter which is only used in Chinese bond market only
*/

#ifndef quantlib_actual365less_day_counter_h
#define quantlib_actual365less_day_counter_h

#include <ql/time/daycounter.hpp>

namespace QuantLib {

    //! Actual/365 (Less) day count convention
    class Actual365Less : public DayCounter {
      private:
        class Impl : public DayCounter::Impl {
          public:
            std::string name() const { return std::string("Actual/365 (Less)"); }
            Time yearFraction(const Date& d1,
                              const Date& d2,
                              const Date&,
                              const Date&) const {

                return dayCount(d1,d2)/365.0;
            }

			BigInteger dayCount(const Date& d1,
				const Date& d2) const {
					Year startDayYear = d1.year();
					Year endDayYear = d2.year();
					BigInteger days = DayCounter::Impl::dayCount(d1,d2);

					for(Year loopYear = startDayYear; loopYear < endDayYear; ++ loopYear) {
						if(QuantLib::Date::isLeap(loopYear)) {
							if(loopYear == startDayYear) {
								if(d1 <= Date(29,Month::February,startDayYear))
									--days;
							} else {
								--days;
							}
						}
					}

					if(QuantLib::Date::isLeap(endDayYear)) {
						Date testDate = Date(29, Month::February, endDayYear);
						if(d2 > testDate && d1 <= testDate)
							--days;
					}

					return days;
			}
        };
      public:
        Actual365Less()
        : DayCounter(boost::shared_ptr<DayCounter::Impl>(
                                                 new Actual365Less::Impl)) {}
    };

}

#endif
