/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) Cheng Li, DataYes

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

#include <ql/instruments/bonds/ctbzerobond.h>
#include <ql/cashflows/simplecashflow.hpp>

namespace QuantLib {

    CTBZeroBond::CTBZeroBond(Natural settlementDays,
							const Calendar& calendar,
							Real faceAmount,
							Real issueValue,
							const Date& issueDate,
							const DayCounter& accrualDayCounter,
							const Date& maturityDate,
							BusinessDayConvention paymentConvention,
							Real redemption)
    : Bond(settlementDays, calendar, issueDate) {
		dayCounter_ = accrualDayCounter;
        maturityDate_ = maturityDate;
		issueValue_ = issueValue;
        Date redemptionDate = calendar_.adjust(maturityDate,
                                               paymentConvention);
        setSingleRedemption(faceAmount, redemption, redemptionDate);
    }

	Real CTBZeroBond::accruedAmount(Date settleDate) const {

		if (settleDate == Date())
            settleDate = settlementDate();

		Real yf = static_cast<Real>(dayCounter_.dayCount(issueDate_, settleDate))/static_cast<Real>(dayCounter_.dayCount(issueDate_, maturityDate_));
		Real totalAmount = (redemption()->amount() - issueValue_);

		return 100.0 / notional(settleDate) * totalAmount * yf;
	}

}
