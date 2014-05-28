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

/*! \file actualactualnl.hpp
    \brief act/act no leap day counters
*/

#ifndef quantlib_actualactual_no_leap_day_counter_h
#define quantlib_actualactual_no_leap_day_counter_h

#include <ql/time/daycounter.hpp>

namespace QuantLib {

    //! Actual/Actual no leap day count
    /*! The day count can be calculated according to:
    */
    class ActualActualNoLeap : public DayCounter {
      private:
        class Impl : public DayCounter::Impl {
          public:
            std::string name() const {
                return std::string("Actual/Actual (NL)");
            }
            Time yearFraction(const Date& d1,
                              const Date& d2,
                              const Date& refPeriodStart,
                              const Date& refPeriodEnd) const;

			BigInteger dayCount(const Date& d1,
                                        const Date& d2) const;
        };
      public:
        ActualActualNoLeap()
        : DayCounter(boost::shared_ptr<DayCounter::Impl>(
                                                 new ActualActualNoLeap::Impl)) {}
    };

}

#endif
