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

/*! \file shiborswap.cpp
    \brief Simple fixed-rate vs Shibor swap
*/

#include <ql/instruments/shiborswap.h>
#include <ql/indexes/ibor/shibor.h>
#include <ql/time/calendars/china.hpp>
#include <ql/time/daycounters/actual360.hpp>

namespace QuantLib {

	ShiborSwap::ShiborSwap(Type type,
		Real nominal,
		Date startDate,
		const Period& swapTenor,
		const Period& fixedTenor,
		Real fixedRate,
		const Period& floatTenor,
        const Handle<YieldTermStructure>& h) 
	    : VanillaSwap(type,
	                  nominal,
					  Schedule(startDate,
					  startDate + swapTenor,
					  fixedTenor,
					  China(),
					  ModifiedFollowing,
					  ModifiedFollowing,
					  DateGeneration::Backward,
					  false),
					  fixedRate,
					  Actual365Fixed(),
					  Schedule(startDate,
					  startDate + swapTenor,
					  floatTenor,
					  China(),
					  ModifiedFollowing,
					  ModifiedFollowing,
					  DateGeneration::Backward,
					  false),
					  floatTenor.units() != Days ? boost::shared_ptr<IborIndex>(new Shibor(floatTenor, h))
											     : boost::shared_ptr<IborIndex>(new DailyTenorShibor(h)),
					  0.0,
					  Actual360(),
					  ModifiedFollowing) {}
	
}
