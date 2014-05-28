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

/*! \file CTBZeroBond.hpp
    \brief zero-coupon china bond; special for China only
*/

#ifndef quantlib_zero_coupon_bond_china_hpp
#define quantlib_zero_coupon_bond_china_hpp

#include <ql/instruments/bond.hpp>
#include <ql/time/daycounter.hpp>

namespace QuantLib {

    //! zero-coupon bond
    /*! \ingroup instruments

        \test calculations are tested by checking results against
              cached values.
    */
    class CTBZeroBond : public Bond {
      public:
        CTBZeroBond(Natural settlementDays,
							const Calendar& calendar,
							Real faceAmount,
							Real issuePrice,
							const Date& issueDate,
							const DayCounter& accrualDayCounter,
							const Date& maturityDate,
							BusinessDayConvention paymentConvention = Following,
							Real redemption = 100.0);

		Real accruedAmount(Date settleDate = Date()) const;
		const DayCounter& dayCounter() const { return dayCounter_; }

	  private:
		Real issueValue_;
		DayCounter dayCounter_;
    };

}

#endif
