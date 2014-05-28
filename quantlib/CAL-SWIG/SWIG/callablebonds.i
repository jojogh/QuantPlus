/*
 Copyright (C) 2013, Cheng Li, DataYes
 Copyright (C) 2006, 2007 StatPro Italia srl

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

#ifndef quantlib_callable_bonds_i
#define quantlib_callable_bonds_i

%include bonds.i
%include callability.i
%include shortratemodels.i

%{
using QuantLib::CallableFixedRateBond;
typedef boost::shared_ptr<Instrument> CallableFixedRateBondPtr;
%}

%rename(CallableFixedRateBond) CallableFixedRateBondPtr;
class CallableFixedRateBondPtr : public BondPtr {
public:
	%extend {
	CallableFixedRateBondPtr(
              Natural settlementDays,
              Real faceAmount,
              const Schedule& schedule,
              const std::vector<Rate>& coupons,
              const DayCounter& accrualDayCounter,
	          const std::vector<boost::shared_ptr<Callability> >& putCallSchedule,
              BusinessDayConvention paymentConvention = Following,
              Real redemption = 100.0,
              const Date& issueDate = Date()) {
            return new CallableFixedRateBondPtr(
                     new CallableFixedRateBond(settlementDays, faceAmount,
                                                   schedule, coupons,
                                                   accrualDayCounter,
                                                   paymentConvention, redemption,
                                                   issueDate, putCallSchedule));
		}
	}
};

%{
using QuantLib::TreeCallableFixedRateBondEngine;
typedef boost::shared_ptr<PricingEngine> TreeCallableFixedRateBondEnginePtr;
%}

%rename(TreeCallableFixedRateBondEngine) TreeCallableFixedRateBondEnginePtr;
class TreeCallableFixedRateBondEnginePtr : public boost::shared_ptr<PricingEngine> {
public:
	%extend {
	TreeCallableFixedRateBondEnginePtr(
			  const boost::shared_ptr<ShortRateModel>& model,
              const Size timeSteps,
              const Handle<YieldTermStructure>& termStructure =
                                                 Handle<YieldTermStructure>()) {
			return new TreeCallableFixedRateBondEnginePtr(
                    new TreeCallableFixedRateBondEngine(model, timeSteps, termStructure));
			}
	}
};

#endif
