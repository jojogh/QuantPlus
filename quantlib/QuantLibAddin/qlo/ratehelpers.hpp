/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005, 2006, 2007 Eric Ehlers
 Copyright (C) 2005 Aurelien Chanudet
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2006, 2007, 2008, 2009, 2012 Ferdinando Ametrano
 Copyright (C) 2007 Marco Bianchetti
 Copyright (C) 2013 Cheng Li

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

#ifndef qla_ratehelpers_hpp
#define qla_ratehelpers_hpp

#include <oh/libraryobject.hpp>

#include <ql/types.hpp>
#include <ql/time/businessdayconvention.hpp>
#include <ql/time/frequency.hpp>
#include <ql/time/dategenerationrule.hpp>

namespace QuantLib {
    class YieldTermStructure;

    template<class TS>
    class BootstrapHelper;

    typedef BootstrapHelper<YieldTermStructure> RateHelper;

    class Quote;
    class Period;
    class Calendar;
    class DayCounter;
    class IborIndex;
	class Shibor;
	class RepoChina;
    class OvernightIndex;
    class SwapIndex;
    class Schedule;
    class Date;
    class Bond;
    template <class T>
    class Handle;
}

namespace QuantLibAddin {

    class RateHelper : public ObjectHandler::LibraryObject<QuantLib::RateHelper> {
      public:
        enum DepoInclusionCriteria {AllDepos,
                                    DeposBeforeFirstFuturesStartDate,
                                    DeposBeforeFirstFuturesStartDatePlusOne,
                                    DeposBeforeFirstFuturesExpiryDate
        };
      protected:
        OH_LIB_CTOR(RateHelper, QuantLib::RateHelper);
    };

    class DepositRateHelper : public RateHelper {
      public:
        DepositRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& rate,
            const boost::shared_ptr<QuantLib::IborIndex>& iborIndex,
            bool permanent);
        DepositRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& quote,
            const QuantLib::Period& p,
            QuantLib::Natural settlementDays,
            const QuantLib::Calendar& calendar,
            QuantLib::BusinessDayConvention convention,
            bool endOfMonth,
            const QuantLib::DayCounter& dayCounter,
            bool permanent);
    };

    class FuturesRateHelper : public RateHelper {
      public:
        FuturesRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& price,
            const QuantLib::Date& immDate,
            const boost::shared_ptr<QuantLib::IborIndex>& iborIndex,
            const QuantLib::Handle<QuantLib::Quote>& convAdj,
            bool permanent);
        FuturesRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& price,
            const QuantLib::Date& immDate,
            QuantLib::Natural lengthInMonths,
            const QuantLib::Calendar& calendar,
            QuantLib::BusinessDayConvention convention,
            bool endOfMonth,
            const QuantLib::DayCounter& dayCounter,
            const QuantLib::Handle<QuantLib::Quote>& convAdj,
            bool permanent);
        FuturesRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& price,
            const QuantLib::Date& immDate,
            const QuantLib::Date& endDate,
            const QuantLib::DayCounter& dayCounter,
            const QuantLib::Handle<QuantLib::Quote>& convAdj,
            bool permanent);
    };

    class SwapRateHelper : public RateHelper {
      public:
        SwapRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& quote,
            const boost::shared_ptr<QuantLib::SwapIndex>& swapIndex,
            const QuantLib::Handle<QuantLib::Quote>& spread,
            const QuantLib::Period& forwardStart,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& discount,
            bool permanent);
        SwapRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& quote,
            const QuantLib::Period& p,
            const QuantLib::Calendar& calendar,
            const QuantLib::Frequency& fixedFrequency,
            QuantLib::BusinessDayConvention fixedConvention,
            const QuantLib::DayCounter& fixedDayCounter,
            const boost::shared_ptr<QuantLib::IborIndex>& iborIndex,
            const QuantLib::Handle<QuantLib::Quote>& spread,
            const QuantLib::Period& forwardStart,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& discount,
            bool permanent);
     };

	class ShiborSwapRateHelper : public RateHelper {
	public:
		ShiborSwapRateHelper(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Handle<QuantLib::Quote>& rate,
			const QuantLib::Period& swapTenor,
			QuantLib::Frequency fixedFreq,
			const boost::shared_ptr<QuantLib::Shibor>& shiborIndex,
			const QuantLib::Period& fwdStart,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountingCurve,
			bool permanent);
	};

	class IBFRSwapRateHelper : public RateHelper {
	public:
		IBFRSwapRateHelper(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Handle<QuantLib::Quote>& rate,
			const QuantLib::Period& swapTenor,
			QuantLib::Frequency payFreq,
			const boost::shared_ptr<QuantLib::RepoChina>& iborIndex,
			const QuantLib::Handle<QuantLib::Quote>& rateSpread,
			const QuantLib::Period& fwdStart,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountingCurve,
			bool permanent);
	};

    class FraRateHelper : public RateHelper {
      public:
        FraRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& rate,
            QuantLib::Period periodToStart,
            const boost::shared_ptr<QuantLib::IborIndex>& iborIndex,
            bool permanent);
        FraRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& rate,
            QuantLib::Period periodToStart,
            QuantLib::Natural lengthInMonths,
            QuantLib::Natural fixingDays,
            const QuantLib::Calendar& calendar,
            QuantLib::BusinessDayConvention convention,
            bool endOfMonth,
            const QuantLib::DayCounter& dayCounter,
            bool permanent);
    };

    class OISRateHelper : public RateHelper {
      public:
        OISRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::Natural settlementDays,
            const QuantLib::Period& tenor, // swap maturity
            const QuantLib::Handle<QuantLib::Quote>& fixedRate,
            const boost::shared_ptr<QuantLib::OvernightIndex>& overnightIndex,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& discount,
            bool permanent);
    };

    class DatedOISRateHelper : public RateHelper {
      public:
        DatedOISRateHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Date& startDate,
            const QuantLib::Date& endDate,
            const QuantLib::Handle<QuantLib::Quote>& fixedRate,
            const boost::shared_ptr<QuantLib::OvernightIndex>& overnightIndex,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& discount,
            bool permanent);
    };

    class BondHelper : public RateHelper {
      public:
        BondHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& price,
            const boost::shared_ptr<QuantLib::Bond>& bond,
			bool useCleanPrice,
            bool permanent);
    };

    class FixedRateBondHelper : public BondHelper {
      public:
        FixedRateBondHelper(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::Quote>& price,
            QuantLib::Natural settlementDays,
            QuantLib::Real faceAmount,
            const boost::shared_ptr<QuantLib::Schedule>& schedule,
            const std::vector<QuantLib::Rate>& coupons,
            const QuantLib::DayCounter& accrualDayCounter,
            QuantLib::BusinessDayConvention paymentConvention,
            QuantLib::Real redemption,
            const QuantLib::Date& issueDate,
			const QuantLib::Calendar& paymentCalendar,
			const QuantLib::Period& exCouponPeriod,
			const QuantLib::Calendar& exCouponCalendar,
			const QuantLib::BusinessDayConvention exCouponConvention,
			bool exCouponEndOfMonth,
			bool useCleanPrice,

            bool permanent);
    };

	class CTBZeroBondHelper : public BondHelper {
	public:
		CTBZeroBondHelper(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Handle<QuantLib::Quote>& cleanPrice,
			QuantLib::Natural settlementDays,
			const QuantLib::Calendar& calendar,
			QuantLib::Real faceAmount,
			QuantLib::Real issuePrice,
			const QuantLib::Date& issueDate,
			const QuantLib::DayCounter& accrualDayCounter,
			const QuantLib::Date& maturityDate,
			QuantLib::BusinessDayConvention paymentConvention,
			QuantLib::Real redemption,
			bool permanent);
	};

	class CTBFixedBondHelper : public BondHelper {
	public:
		CTBFixedBondHelper(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Handle<QuantLib::Quote>& cleanPrice,
			const QuantLib::Date& issueDate,
			QuantLib::Natural settlementDays,
			QuantLib::Real faceAmount,
			const QuantLib::Date& startDate,
			const QuantLib::Date& maturity,
			const QuantLib::Period& tenor,			   
			const std::vector<QuantLib::Rate>& coupons,
			const QuantLib::DayCounter& accrualDayCounter,
			bool endOfMonth,
			const QuantLib::Calendar& calendar,
			const QuantLib::Calendar& paymentCalendar,
			QuantLib::BusinessDayConvention convention,
			QuantLib::DateGeneration::Rule rule,
			QuantLib::BusinessDayConvention paymentConvention,
			QuantLib::Real redemption,
			const QuantLib::Date& firstDate,
			const QuantLib::Date& nextToLastDate,
			bool permanent);
	};


    // Processes the set of curve bootstrapping instruments
    // and selects a subset according to the given rules and parameters
    std::vector<std::string> CALRateHelperSelection(
        const std::vector<boost::shared_ptr<QuantLibAddin::RateHelper> >& qlarhs,
        const std::vector<QuantLib::Natural>& priority,
        QuantLib::Natural nImmFutures,
        QuantLib::Natural nSerialFutures,
        QuantLib::Natural frontFuturesRollingDays,
        RateHelper::DepoInclusionCriteria depoInclusionCriteria,
        const std::vector<QuantLib::Natural>& minDistance);

    // Returns the rate, if any, associated to the given rate helper
    QuantLib::Real CALRateHelperRate(
        const boost::shared_ptr<QuantLibAddin::RateHelper>& qlarh);

}

#endif
