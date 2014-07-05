
/*
 Copyright (C) 2005, 2006, 2007, 2008 StatPro Italia srl
 Copyright (C) 2009 Joseph Malicki

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

#ifndef quantlib_rate_helpers_i
#define quantlib_rate_helpers_i

%include bonds.i
%include date.i
%include calendars.i
%include daycounters.i
%include marketelements.i
%include types.i
%include vectors.i
%include swap.i

%{
using QuantLib::RateHelper;
using QuantLib::DepositRateHelper;
using QuantLib::FraRateHelper;
using QuantLib::FuturesRateHelper;
using QuantLib::SwapRateHelper;
using QuantLib::BondHelper;
using QuantLib::ShiborSwapRateHelper;
using QuantLib::IBFRSwapRateHelper;
using QuantLib::FixedRateBondHelper;
using QuantLib::CTBZeroBondHelper;
using QuantLib::CTBFixedBondHelper;
using QuantLib::OISRateHelper;
using QuantLib::DatedOISRateHelper;
typedef boost::shared_ptr<RateHelper> DepositRateHelperPtr;
typedef boost::shared_ptr<RateHelper> FraRateHelperPtr;
typedef boost::shared_ptr<RateHelper> FuturesRateHelperPtr;
typedef boost::shared_ptr<RateHelper> SwapRateHelperPtr;
typedef boost::shared_ptr<RateHelper> BondHelperPtr;
typedef boost::shared_ptr<RateHelper> ShiborSwapRateHelperPtr;
typedef boost::shared_ptr<RateHelper> IBFRSwapRateHelperPtr;
typedef boost::shared_ptr<RateHelper> FixedRateBondHelperPtr;
typedef boost::shared_ptr<RateHelper> CTBZeroBondHelperPtr;
typedef boost::shared_ptr<RateHelper> CTBFixedBondHelperPtr;
typedef boost::shared_ptr<RateHelper> OISRateHelperPtr;
typedef boost::shared_ptr<RateHelper> DatedOISRateHelperPtr;
%}

%ignore RateHelper;
class RateHelper {
    #if defined(SWIGMZSCHEME) || defined(SWIGGUILE)
    %rename("latest-date") latestDate;
    #endif
  public:
    Handle<Quote> quote() const;
    Date latestDate() const;
};

// rate helpers for curve bootstrapping
%template(RateHelper) boost::shared_ptr<RateHelper>;

%rename(DepositRateHelper) DepositRateHelperPtr;
class DepositRateHelperPtr : public boost::shared_ptr<RateHelper> {
  public:
    %extend {
        DepositRateHelperPtr(
                const Handle<Quote>& rate,
                const Period& tenor,
                Natural fixingDays,
                const Calendar& calendar,
                BusinessDayConvention convention,
                bool endOfMonth,
                const DayCounter& dayCounter) {
            return new DepositRateHelperPtr(
                new DepositRateHelper(rate,tenor,fixingDays,
                                      calendar,convention,
                                      endOfMonth, dayCounter));
        }
        DepositRateHelperPtr(
                Rate rate,
                const Period& tenor,
                Natural fixingDays,
                const Calendar& calendar,
                BusinessDayConvention convention,
                bool endOfMonth,
                const DayCounter& dayCounter) {
            return new DepositRateHelperPtr(
                new DepositRateHelper(rate, tenor, fixingDays,
                                      calendar, convention,
                                      endOfMonth, dayCounter));
        }
        DepositRateHelperPtr(const Handle<Quote>& rate,
                             const IborIndexPtr& index) {
            boost::shared_ptr<IborIndex> libor =
                boost::dynamic_pointer_cast<IborIndex>(index);
            return new DepositRateHelperPtr(
                new DepositRateHelper(rate, libor));
        }
        DepositRateHelperPtr(Rate rate,
                             const IborIndexPtr& index) {
            boost::shared_ptr<IborIndex> libor =
                boost::dynamic_pointer_cast<IborIndex>(index);
            return new DepositRateHelperPtr(
                new DepositRateHelper(rate, libor));
        }

    }
};

%rename(FraRateHelper) FraRateHelperPtr;
class FraRateHelperPtr : public boost::shared_ptr<RateHelper> {
  public:
    %extend {
        FraRateHelperPtr(
                const Handle<Quote>& rate,
                Natural monthsToStart,
                Natural monthsToEnd,
                Natural fixingDays,
                const Calendar& calendar,
                BusinessDayConvention convention,
                bool endOfMonth,
                const DayCounter& dayCounter) {
            return new FraRateHelperPtr(
                new FraRateHelper(rate,monthsToStart,monthsToEnd,
                                  fixingDays,calendar,convention,
                                  endOfMonth,dayCounter));
        }
        FraRateHelperPtr(
                Rate rate,
                Natural monthsToStart,
                Natural monthsToEnd,
                Natural fixingDays,
                const Calendar& calendar,
                BusinessDayConvention convention,
                bool endOfMonth,
                const DayCounter& dayCounter) {
            return new FraRateHelperPtr(
                new FraRateHelper(rate,monthsToStart,monthsToEnd,
                                  fixingDays,calendar,convention,
                                  endOfMonth,dayCounter));
        }
        FraRateHelperPtr(const Handle<Quote>& rate,
                         Natural monthsToStart,
                         const IborIndexPtr& index) {
            boost::shared_ptr<IborIndex> libor =
                boost::dynamic_pointer_cast<IborIndex>(index);
            return new FraRateHelperPtr(
                new FraRateHelper(rate,monthsToStart,libor));
        }
        FraRateHelperPtr(Rate rate,
                         Natural monthsToStart,
                         const IborIndexPtr& index) {
            boost::shared_ptr<IborIndex> libor =
                boost::dynamic_pointer_cast<IborIndex>(index);
            return new FraRateHelperPtr(
                new FraRateHelper(rate,monthsToStart,libor));
        }

    }
};

%rename(FuturesRateHelper) FuturesRateHelperPtr;
class FuturesRateHelperPtr : public boost::shared_ptr<RateHelper> {
  public:
    %extend {
        FuturesRateHelperPtr(
                const Handle<Quote>& price,
                const Date& immDate,
                Natural nMonths,
                const Calendar& calendar,
                BusinessDayConvention convention,
                bool endOfMonth,
                const DayCounter& dayCounter,
                const Handle<Quote>& convexityAdjustment) {
            return new FuturesRateHelperPtr(
                new FuturesRateHelper(price,immDate,nMonths,
                                      calendar,convention,endOfMonth,
                                      dayCounter,convexityAdjustment));
        }
        FuturesRateHelperPtr(
                Real price, const Date& immDate, Natural nMonths,
                const Calendar& calendar, BusinessDayConvention convention,
                bool endOfMonth, const DayCounter& dayCounter,
                Rate convexityAdjustment = 0.0) {
            return new FuturesRateHelperPtr(
                new FuturesRateHelper(price,immDate,nMonths,
                                      calendar,convention,endOfMonth,
                                      dayCounter,convexityAdjustment));
        }
        FuturesRateHelperPtr(
                const Handle<Quote>& price,
                const Date& immDate,
                const IborIndexPtr& index,
                const Handle<Quote>& convexityAdjustment) {
            boost::shared_ptr<IborIndex> libor =
                boost::dynamic_pointer_cast<IborIndex>(index);
            return new FuturesRateHelperPtr(
                new FuturesRateHelper(price,immDate,libor,
                                      convexityAdjustment));
        }
        FuturesRateHelperPtr(
                Real price,
                const Date& immDate,
                const IborIndexPtr& index,
                Real convexityAdjustment = 0.0) {
            boost::shared_ptr<IborIndex> libor =
                boost::dynamic_pointer_cast<IborIndex>(index);
            return new FuturesRateHelperPtr(
                new FuturesRateHelper(price,immDate,libor,
                                      convexityAdjustment));
        }

    }
};

%rename(SwapRateHelper) SwapRateHelperPtr;
class SwapRateHelperPtr : public boost::shared_ptr<RateHelper> {
  public:
    %extend {
        SwapRateHelperPtr(
                const Handle<Quote>& rate,
                const Period& tenor,
                const Calendar& calendar,
                Frequency fixedFrequency,
                BusinessDayConvention fixedConvention,
                const DayCounter& fixedDayCount,
                const IborIndexPtr& index,
                const Handle<Quote>& spread = Handle<Quote>(),
                const Period& fwdStart = 0*Days,
                const Handle<YieldTermStructure>& discountingCurve
                                    = Handle<YieldTermStructure>()) {

            boost::shared_ptr<IborIndex> libor =
                boost::dynamic_pointer_cast<IborIndex>(index);
            return new SwapRateHelperPtr(
                new SwapRateHelper(rate, tenor, calendar,
                                   fixedFrequency, fixedConvention,
                                   fixedDayCount, libor,
                                   spread, fwdStart,
                                   discountingCurve));
        }
        SwapRateHelperPtr(
                Rate rate,
                const Period& tenor,
                const Calendar& calendar,
                Frequency fixedFrequency,
                BusinessDayConvention fixedConvention,
                const DayCounter& fixedDayCount,
                const IborIndexPtr& index,
                const Handle<Quote>& spread = Handle<Quote>(),
                const Period& fwdStart = 0*Days,
                const Handle<YieldTermStructure>& discountingCurve
                                    = Handle<YieldTermStructure>()) {
            boost::shared_ptr<IborIndex> libor =
                boost::dynamic_pointer_cast<IborIndex>(index);
            return new SwapRateHelperPtr(
                new SwapRateHelper(rate, tenor, calendar,
                                   fixedFrequency, fixedConvention,
                                   fixedDayCount, libor,
                                   spread, fwdStart,
                                   discountingCurve));
        }
        SwapRateHelperPtr(
                const Handle<Quote>& rate,
                const SwapIndexPtr& index,
                const Handle<Quote>& spread = Handle<Quote>(),
                const Period& fwdStart = 0*Days,
                const Handle<YieldTermStructure>& discountingCurve
                                    = Handle<YieldTermStructure>()) {
            boost::shared_ptr<SwapIndex> swapIndex =
                boost::dynamic_pointer_cast<SwapIndex>(index);
            return new SwapRateHelperPtr(
                new SwapRateHelper(rate, swapIndex,
                                   spread, fwdStart,
                                   discountingCurve));
        }
        SwapRateHelperPtr(
                Rate rate,
                const SwapIndexPtr& index,
                const Handle<Quote>& spread = Handle<Quote>(),
                const Period& fwdStart = 0*Days,
                const Handle<YieldTermStructure>& discountingCurve
                                    = Handle<YieldTermStructure>()) {
            boost::shared_ptr<SwapIndex> swapIndex =
                boost::dynamic_pointer_cast<SwapIndex>(index);
            return new SwapRateHelperPtr(
                new SwapRateHelper(rate, swapIndex,
                                   spread, fwdStart,
                                   discountingCurve));
        }

        VanillaSwapPtr swap() {
            return boost::dynamic_pointer_cast<SwapRateHelper>(*self)->swap();
        }
    }
};

%rename(BondHelper) BondHelperPtr;
class BondHelperPtr : public boost::shared_ptr<RateHelper> {
  public:
    %extend {
        BondHelperPtr(const Handle<Quote>& cleanPrice,
                      const BondPtr& bond,
                      bool useCleanPrice = true) {
            boost::shared_ptr<Bond> b = boost::dynamic_pointer_cast<Bond>(bond);
            return new BondHelperPtr(
                new BondHelper(cleanPrice, b, useCleanPrice));
        }

        BondPtr bond() {
            return BondPtr(boost::dynamic_pointer_cast<BondHelper>(*self)->bond());
        }
    }
};


%rename(ShiborSwapRateHelper) ShiborSwapRateHelperPtr;
class ShiborSwapRateHelperPtr : public boost::shared_ptr<RateHelper> {
  public:
    %extend {
        ShiborSwapRateHelperPtr(
            const Handle<Quote>& rate,
			const Period& swapTenor,
			Frequency fixedFreq,
			const ShiborPtr& shiborIndex,
			const Period& fwdStart = 0*Days) {
            boost::shared_ptr<Shibor> shibor =
                boost::dynamic_pointer_cast<Shibor>(shiborIndex);
            return new ShiborSwapRateHelperPtr(
                new ShiborSwapRateHelper(rate, swapTenor,
                                   fixedFreq, 
                                   shibor,
                                   fwdStart));
        }
        VanillaSwapPtr swap() {
            return boost::dynamic_pointer_cast<ShiborSwapRateHelper>(*self)->swap();
        }
    }
};

%rename(IBFRSwapRateHelper) IBFRSwapRateHelperPtr;
class IBFRSwapRateHelperPtr : public boost::shared_ptr<RateHelper> {
  public:
    %extend {
        IBFRSwapRateHelperPtr(
            const Handle<Quote>& rate,
			const Period& swapTenor,
			Frequency payFreq,
			const RepoChinaPtr& repoIndex,
			const Handle<Quote> rateSpread = Handle<Quote>(),
			const Period& fwdStart = 0*Days) {
            boost::shared_ptr<RepoChina> repo =
                boost::dynamic_pointer_cast<RepoChina>(repoIndex);
            return new IBFRSwapRateHelperPtr(
                new IBFRSwapRateHelper(rate, swapTenor,
                                   payFreq, 
                                   repo,
								   rateSpread,
                                   fwdStart));
        }
        IBFRSwapPtr swap() {
            return boost::dynamic_pointer_cast<ShiborSwapRateHelper>(*self)->swap();
        }
    }
};


%rename(FixedRateBondHelper) FixedRateBondHelperPtr;
class FixedRateBondHelperPtr : public BondHelperPtr {
  public:
    %extend {
        FixedRateBondHelperPtr(
                      const Handle<Quote>& cleanPrice,
                      Size settlementDays,
                      Real faceAmount,
                      const Schedule& schedule,
                      const std::vector<Rate>& coupons,
                      const DayCounter& paymentDayCounter,
                      BusinessDayConvention paymentConvention = Following,
                      Real redemption = 100.0,
                      const Date& issueDate = Date(),
                      const Calendar& paymentCalendar = Calendar(),
                      const Period& exCouponPeriod = Period(),
                      const Calendar& exCouponCalendar = Calendar(),
                      BusinessDayConvention exCouponConvention = Unadjusted,
                      bool exCouponEndOfMonth = false,
                      bool useCleanPrice = true) {
            return new FixedRateBondHelperPtr(
                new FixedRateBondHelper(cleanPrice, settlementDays, faceAmount,
                                        schedule, coupons, paymentDayCounter,
                                        paymentConvention, redemption,
                                        issueDate, paymentCalendar,
                                        exCouponPeriod, exCouponCalendar,
                                        exCouponConvention, exCouponEndOfMonth,
                                        useCleanPrice));
        }

        FixedRateBondPtr bond() {
            return FixedRateBondPtr(boost::dynamic_pointer_cast<FixedRateBondHelper>(*self)->bond());
        }
    }
};

%rename(CTBZeroBondHelper) CTBZeroBondHelperPtr;
class CTBZeroBondHelperPtr : public BondHelperPtr {
  public:
    %extend {
        CTBZeroBondHelperPtr(const Handle<Quote>& cleanPrice,
			Natural settlementDays,
			const Calendar& calendar,
			Real faceAmount,
			Real issuePrice,
			const Date& issueDate,
			const DayCounter& accrualDayCounter,
			const Date& maturityDate,
			BusinessDayConvention paymentConvention = Following,
			Real redemption = 100.0) {
            return new CTBZeroBondHelperPtr(
                new CTBZeroBondHelper(cleanPrice, settlementDays,
											      calendar,
												  faceAmount,
												  issuePrice,
												  issueDate,
												  accrualDayCounter,
												  maturityDate,
											      paymentConvention,
												  redemption));
        }

        CTBZeroBondPtr bond() {
            return CTBZeroBondPtr(boost::dynamic_pointer_cast<CTBZeroBondHelper>(*self)->bond());
        }
    }
};

%rename(CTBFixedBondHelper) CTBFixedBondHelperPtr;
class CTBFixedBondHelperPtr : public BondHelperPtr {
  public:
    %extend {
        CTBFixedBondHelperPtr(const Handle<Quote>& cleanPrice,
			Natural settlementDays,
			Real faceAmount,
			const Date& startDate,
			const Date& maturity,
			const Period& tenor,			   
			const std::vector<Rate>& coupons,
			const DayCounter& accrualDayCounter = QuantLib::ActualActualNoLeap(),
			bool endOfMonth = false,
			const Calendar& calendar = QuantLib::NullCalendar(),
			const Calendar& paymentCalendar = QuantLib::China(),
			BusinessDayConvention convention = Unadjusted,
			DateGeneration::Rule rule = DateGeneration::Backward,
			BusinessDayConvention paymentConvention = Unadjusted,
			Real redemption = 100.0,
			const Date& firstDate = Date(),
			const Date& nextToLastDate = Date(),
			const Date& issueDate = Date()) {
            return new CTBFixedBondHelperPtr(
                new CTBFixedBondHelper(cleanPrice, issueDate,
																 settlementDays,
																 faceAmount,
																 startDate,
																 maturity,
																 tenor,
																 coupons,
																 accrualDayCounter,
																 endOfMonth,
																 calendar,
																 paymentCalendar,
																 convention,
																 rule,
																 paymentConvention,
																 redemption,
																 firstDate,
																 nextToLastDate));
        }

        CTBFixedBondPtr bond() {
            return CTBFixedBondPtr(boost::dynamic_pointer_cast<CTBFixedBondHelper>(*self)->bond());
        }
    }
};

%rename(OISRateHelper) OISRateHelperPtr;
class OISRateHelperPtr : public boost::shared_ptr<RateHelper> {
  public:
    %extend {
        OISRateHelperPtr(
                Natural settlementDays,
                const Period& tenor,
                const Handle<Quote>& rate,
                const OvernightIndexPtr& index,
                const Handle<YieldTermStructure>& discountingCurve
                                            = Handle<YieldTermStructure>()) {
            boost::shared_ptr<OvernightIndex> overnight =
                boost::dynamic_pointer_cast<OvernightIndex>(index);
            return new OISRateHelperPtr(
                new OISRateHelper(settlementDays,tenor,rate,
                                  overnight,discountingCurve));
        }
    }
};

%rename(DatedOISRateHelper) DatedOISRateHelperPtr;
class DatedOISRateHelperPtr : public boost::shared_ptr<RateHelper> {
  public:
    %extend {
        DatedOISRateHelperPtr(
                const Date& startDate,
                const Date& endDate,
                const Handle<Quote>& rate,
                const OvernightIndexPtr& index,
                const Handle<YieldTermStructure>& discountingCurve
                                            = Handle<YieldTermStructure>()) {
            boost::shared_ptr<OvernightIndex> overnight =
                boost::dynamic_pointer_cast<OvernightIndex>(index);
            return new DatedOISRateHelperPtr(
                new DatedOISRateHelper(startDate,endDate,rate,
                                       overnight,discountingCurve));
        }
    }
};


// allow use of RateHelper vectors
#if defined(SWIGCSHARP)
SWIG_STD_VECTOR_ENHANCED( boost::shared_ptr<RateHelper> )
#endif
namespace std {
    %template(RateHelperVector) vector<boost::shared_ptr<RateHelper> >;
}


#endif
