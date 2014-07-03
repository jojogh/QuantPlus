/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006, 2007 Chiara Fornarola
 Copyright (C) 2006, 2007, 2008, 2009, 2010, 2011 Ferdinando Ametrano
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Walter Penschke
 Copyright (C) 2009 Piter Dias
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

#ifndef qla_bonds_hpp
#define qla_bonds_hpp

#include <qlo/baseinstruments.hpp>
#include <qlo/leg.hpp>

#include <ql/currency.hpp>
#include <ql/instruments/bond.hpp>
#include <ql/time/dategenerationrule.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/calendars/china.hpp>
#include <ql/instruments/callabilityschedule.hpp>
#include <ql/experimental/amortizingbonds/amortizingfixedratebond.hpp>

#include <string>

namespace QuantLib {
    class FloatingRateCouponPricer;
    class SwapIndex;
    class IborIndex;
    class Schedule;
    class Calendar;
    class Date;
    class DayCounter;
    class YieldTermStructure;
}

namespace QuantLibAddin {

    class Bond : public Instrument {
      public:
        const std::string& description();
        std::string currency() { return currency_.code(); }
        //QuantLib::Currency currency();
        QuantLib::Real redemptionAmount();
        QuantLib::Date redemptionDate();
        void setCouponPricer(
            const boost::shared_ptr<QuantLib::FloatingRateCouponPricer>&);
        void setCouponPricers(
            const std::vector<boost::shared_ptr<QuantLib::FloatingRateCouponPricer> >&);
        std::vector<std::vector<ObjectHandler::property_t> > flowAnalysis(
                                                    const QuantLib::Date& d);
        Bond(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
             const std::string& description,
             const QuantLib::Currency& currency,
             QuantLib::Natural settlementDays,
             const QuantLib::Calendar& calendar,
             QuantLib::Real faceAmount,
             const QuantLib::Date& maturityDate,
             const QuantLib::Date& issueDate,
             const QuantLib::Leg& leg,
             bool permanent);
      protected:
        Bond(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
             const std::string& description,
             const QuantLib::Currency& currency,
             bool permanent);
        std::string description_;
        QuantLib::Currency currency_;
        boost::shared_ptr<QuantLib::Bond> qlBondObject_;
    };

    class ZeroCouponBond : public Bond {
      public:
        ZeroCouponBond(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& des,
            const QuantLib::Currency& cur,
            QuantLib::Natural settlementDays,
            const QuantLib::Calendar& calendar,
            QuantLib::Real faceAmount,
            const QuantLib::Date& maturityDate,
            QuantLib::BusinessDayConvention paymentConvention,
            QuantLib::Real redemption,
            const QuantLib::Date& issueDate,
            bool permanent);
    };

	class CTBZeroBond : public Bond {

	public:
		CTBZeroBond(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const std::string& des,
			const QuantLib::Currency& cur,
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

    class FixedRateBond : public Bond {
      public:
        FixedRateBond(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& des,
            const QuantLib::Currency& cur,
            QuantLib::Natural settlementDays,
            QuantLib::Real faceAmount,
            const boost::shared_ptr<QuantLib::Schedule>& schedule,
            const std::vector<QuantLib::Rate>& coupons,
            const QuantLib::DayCounter& accrualDayCounter,
            QuantLib::BusinessDayConvention paymentConvention,
            QuantLib::Real redemption,
            const QuantLib::Date& issueDate,
            const QuantLib::Calendar& paymentCalendar,
            bool permanent);
        FixedRateBond(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& des,
            const QuantLib::Currency& cur,
            QuantLib::Natural settlementDays,
            QuantLib::Real faceAmount,
            const boost::shared_ptr<QuantLib::Schedule>& schedule,
            const std::vector<boost::shared_ptr<QuantLib::InterestRate> >& coupons,
            QuantLib::BusinessDayConvention paymentConvention,
            QuantLib::Real redemption,
            const QuantLib::Date& issueDate,
            const QuantLib::Calendar& paymentCalendar,
			bool permanent);		
			// Special functions for Treasury bond futures
			QuantLib::Real conversionFactor(QuantLib::Year year, QuantLib::Month month, QuantLib::Rate benchmarkRate) const ;

			QuantLib::Real impliedRepoRate(QuantLib::Date settlementDate,
					QuantLib::Real futurePrice, QuantLib::Real cleanPrice,
					QuantLib::Year year, QuantLib::Month month, QuantLib::Rate benchmarkRate,
					const QuantLib::DayCounter& repoDayCounter, 
					const QuantLib::Calendar& dayCalendar) const;
			QuantLib::Real netBasis(QuantLib::Real futurePrice, QuantLib::Real cleanPrice, 
					QuantLib::Year year, QuantLib::Month month, QuantLib::Rate benchmarkRate) const;

      protected:
        FixedRateBond(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& description,
            const QuantLib::Currency& currency,
            bool permanent);
    };

	class CTBFixedBond : public FixedRateBond {

	public:
		CTBFixedBond(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const std::string& des,
			const QuantLib::Currency& cur,
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

    class FloatingRateBond : public Bond {
      public:
        FloatingRateBond(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& des,
            const QuantLib::Currency& cur,
            QuantLib::Natural settlementDays,
            QuantLib::BusinessDayConvention paymentConvention,
            QuantLib::Real faceAmount,
            const boost::shared_ptr<QuantLib::Schedule>& schedule,
            QuantLib::Natural fixingDays,
            bool inArrears,
            const QuantLib::DayCounter& paymentDayCounter,
            const std::vector<QuantLib::Rate>& floors,
            const std::vector<QuantLib::Real>& gearings,
            const boost::shared_ptr<QuantLib::IborIndex>& index,
            const std::vector<QuantLib::Spread>& spreads,
            const std::vector<QuantLib::Rate>& caps,
            QuantLib::Real redemption,
            const QuantLib::Date& issueDate,
            bool permanent);
        // add constructor without schedule
      protected:
        FloatingRateBond(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& description,
            const QuantLib::Currency& currency,
            bool permanent);
    };

    class CmsRateBond : public Bond {
      public:
        CmsRateBond(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& des,
            const QuantLib::Currency& cur,
            QuantLib::Natural settlementDays,
            QuantLib::BusinessDayConvention paymentConvention,
            QuantLib::Real faceAmount,
            const boost::shared_ptr<QuantLib::Schedule>& schedule,
            QuantLib::Natural fixingDays,
            bool inArrears,
            const QuantLib::DayCounter& paymentDayCounter,
            const std::vector<QuantLib::Rate>& floors,
            const std::vector<QuantLib::Real>& gearings,
            const boost::shared_ptr<QuantLib::SwapIndex>& index,
            const std::vector<QuantLib::Spread>& spreads,
            const std::vector<QuantLib::Rate>& caps,
            QuantLib::Real redemption,
            const QuantLib::Date& issueDate,
            bool permanent);
        // add constructor without schedule
    };

	class AmortizingFixedRateBond : public Bond {
	public:
		AmortizingFixedRateBond(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const std::string& des,
			const QuantLib::Currency& cur,
			QuantLib::Natural settlementDays,
			const QuantLib::Calendar& calendar,
			QuantLib::Real faceAmount,
			const QuantLib::Date& startDate,
			const QuantLib::Period& bondTenor,
			const QuantLib::Frequency& sinkingFrequency,
			const QuantLib::Rate& coupon,
			const QuantLib::DayCounter& accrualDayCounter,
            const QuantLib::Calendar& paymentCalendar,
			QuantLib::BusinessDayConvention paymentConvention,
			QuantLib::AmortizingFixedRateBond::AmortizingType type,
			const QuantLib::Date& issueDate,
			bool permanent);

		AmortizingFixedRateBond(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const std::string& des,
			const QuantLib::Currency& cur,
			QuantLib::Natural settlementDays,
			const QuantLib::Calendar& calendar,
			QuantLib::Real startAmount,
			QuantLib::Real endAmount,
			const QuantLib::Date& startDate,
			const QuantLib::Period& bondTenor,
			const QuantLib::Frequency& sinkingFrequency,
			const QuantLib::Rate& coupon,
			const QuantLib::DayCounter& accrualDayCounter,
            const QuantLib::Calendar& paymentCalendar,
			QuantLib::BusinessDayConvention paymentConvention,
			QuantLib::AmortizingFixedRateBond::AmortizingType type,
			const QuantLib::Date& issueDate,
			bool permanent);
	};

    std::vector<std::string> CALBondAlive(
                        const std::vector<boost::shared_ptr<Bond> >& bonds,
                        QuantLib::Date& refDate);

    std::string CALBondMaturityLookup(
                        const std::vector<boost::shared_ptr<Bond> >& bonds,
                        const QuantLib::Date& maturity);

    std::vector<std::string> CALBondMaturitySort(
                        const std::vector<boost::shared_ptr<Bond> >& bonds);

	// Callable bond stuff
	class Callability : public ObjectHandler::LibraryObject<QuantLib::Callability> {
	public:
		Callability(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			QuantLib::Callability::Price::Type priceType,
			QuantLib::Real amount,
			QuantLib::Callability::Type callabilityType,
			const QuantLib::Date& callDate,
			bool permanent);
	protected:
		OH_LIB_CTOR(Callability, QuantLib::Callability)
	};

	class CallabilitySchedule : public ObjectHandler::LibraryObject<QuantLib::CallabilitySchedule> {
	public:
		CallabilitySchedule(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                const std::vector<boost::shared_ptr<QuantLib::Callability> >& Callabilities,
							bool permanent);
	protected:
		OH_LIB_CTOR(CallabilitySchedule, QuantLib::CallabilitySchedule)
	};

	class CallableFixedRateBond : public Bond {
	public:
		CallableFixedRateBond(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const std::string& des,
			const QuantLib::Currency& cur,
			QuantLib::Natural settlementDays,
			QuantLib::Real faceAmount,
			const boost::shared_ptr<QuantLib::Schedule>& schedule,
			const std::vector<QuantLib::Rate>& coupons,
			const QuantLib::DayCounter& accrualDayCounter,
			QuantLib::BusinessDayConvention paymentConvention,
			QuantLib::Real redemption,
			const QuantLib::Date& issueDate,
			const boost::shared_ptr<QuantLib::CallabilitySchedule>& putCallSchedule,
			bool permanent);
	};

}

#endif
