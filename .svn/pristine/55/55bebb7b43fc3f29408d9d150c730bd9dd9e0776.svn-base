/*
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
 Copyright (C) 2007 StatPro Italia srl
 Copyright (C) 2011 Lluis Pujol Bajador
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

#ifndef quantlib_swap_i
#define quantlib_swap_i

%include instruments.i
%include termstructures.i
%include cashflows.i
%include timebasket.i

%{
using QuantLib::Swap;
using QuantLib::VanillaSwap;
using QuantLib::ShiborSwap;
using QuantLib::IBFRSwap;
using QuantLib::DiscountingSwapEngine;

typedef boost::shared_ptr<Instrument> SwapPtr;
typedef boost::shared_ptr<Instrument> VanillaSwapPtr;
typedef boost::shared_ptr<Instrument> ShiborSwapPtr;
typedef boost::shared_ptr<Instrument> IBFRSwapPtr;
typedef boost::shared_ptr<PricingEngine> DiscountingSwapEnginePtr;
%}

%rename(Swap) SwapPtr;
class SwapPtr : public boost::shared_ptr<Instrument> {
  public:
    %extend {
        SwapPtr(const std::vector<boost::shared_ptr<CashFlow> >& firstLeg,
                const std::vector<boost::shared_ptr<CashFlow> >& secondLeg) {
            return new SwapPtr(new Swap(firstLeg, secondLeg));
        }
        Date startDate() {
            return boost::dynamic_pointer_cast<Swap>(*self)->startDate();
        }
        Date maturityDate() {
            return boost::dynamic_pointer_cast<Swap>(*self)->maturityDate();
        }
    }
};


#if defined(SWIGJAVA) || defined(SWIGCSHARP)
%rename(_VanillaSwap) VanillaSwap;
#else
%ignore VanillaSwap;
#endif
class VanillaSwap {
  public:
    enum Type { Receiver = -1, Payer = 1 };
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
  private:
    VanillaSwap();
#endif
};

%rename(VanillaSwap) VanillaSwapPtr;
class VanillaSwapPtr : public SwapPtr {
    #if defined(SWIGMZSCHEME) || defined(SWIGGUILE)
    %rename("fair-rate")            fairRate;
    %rename("fair-spread")          fairSpread;
    %rename("fixed-leg-BPS")    	fixedLegBPS;
    %rename("floating-leg-BPS") 	floatingLegBPS;
	%rename("fixed-leg") 			fixedLeg;
	%rename("floating-leg") 		floatingLeg;
	%rename("fixed-schedule") 		fixedSchedule;
	%rename("floating-schedule") 	floatingSchedule;
	%rename("ibor-index")           iborIndex;
    #endif
  public:
    %extend {
        static const VanillaSwap::Type Receiver = VanillaSwap::Receiver;
        static const VanillaSwap::Type Payer = VanillaSwap::Payer;
        VanillaSwapPtr(VanillaSwap::Type type, Real nominal,
                       const Schedule& fixedSchedule, Rate fixedRate,
                       const DayCounter& fixedDayCount,
                       const Schedule& floatSchedule,
                       const IborIndexPtr& index,
                       Spread spread,
                       const DayCounter& floatingDayCount) {
            boost::shared_ptr<IborIndex> libor =
                boost::dynamic_pointer_cast<IborIndex>(index);
            return new VanillaSwapPtr(
                    new VanillaSwap(type, nominal,fixedSchedule,fixedRate,
                                    fixedDayCount,floatSchedule,libor,
                                    spread, floatingDayCount));
        }
        Rate fairRate() {
            return boost::dynamic_pointer_cast<VanillaSwap>(*self)->fairRate();
        }
        Spread fairSpread() {
            return boost::dynamic_pointer_cast<VanillaSwap>(*self)
                 ->fairSpread();
        }
        Real fixedLegBPS() {
            return boost::dynamic_pointer_cast<VanillaSwap>(*self)
                 ->fixedLegBPS();
        }
        Real floatingLegBPS() {
            return boost::dynamic_pointer_cast<VanillaSwap>(*self)
                 ->floatingLegBPS();
        }
		
		const Leg& fixedLeg() const {
		
			return boost::dynamic_pointer_cast<VanillaSwap>(*self)
				 ->fixedLeg();		
		}
		
		const Leg& floatingLeg() const {
		
			return boost::dynamic_pointer_cast<VanillaSwap>(*self)
				 ->floatingLeg();		
		}
		
		const Schedule& floatingSchedule() const {
			return boost::dynamic_pointer_cast<VanillaSwap>(*self)
				 ->floatingSchedule();				
		}
		
		const Schedule& fixedSchedule() const {
			return boost::dynamic_pointer_cast<VanillaSwap>(*self)
				 ->fixedSchedule();				
		}
		
		const boost::shared_ptr<IborIndex>& iborIndex() const {
			return boost::dynamic_pointer_cast<VanillaSwap>(*self)
				 ->iborIndex();				
		}
    }
};

%rename(ShiborSwap) ShiborSwapPtr;
class ShiborSwapPtr : public VanillaSwapPtr {
  public:
    %extend {
        ShiborSwapPtr(VanillaSwap::Type type, Real nominal, Date startDate,
					   const Period& swapTenor,
                       const Period& fixedTenor, Rate fixedRate,
                       const Period& floatTenor,
		       const Handle<YieldTermStructure>& h) {
            return new ShiborSwapPtr(
                    new ShiborSwap(type,nominal,startDate,swapTenor,
                                    fixedTenor,fixedRate,floatTenor, h));
        }
    }
};

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
%rename(_IBFRSwap) IBFRSwap;
#else
%ignore IBFRSwap;
#endif
class IBFRSwap {
  public:
    enum Type { Receiver = -1, Payer = 1 };
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
  private:
    IBFRSwap();
#endif
};

%rename(IBFRSwap) IBFRSwapPtr;
class IBFRSwapPtr : public SwapPtr {
    #if defined(SWIGMZSCHEME) || defined(SWIGGUILE)
    %rename("fair-rate")            fairRate;
    %rename("fair-spread")          fairSpread;
    %rename("fixed-leg-BPS")    	fixedLegBPS;
    %rename("floating-leg-BPS") 	floatingLegBPS;
	%rename("fixed-leg") 			fixedLeg;
	%rename("floating-leg") 		floatingLeg;
	%rename("fixed-schedule") 		fixedSchedule;
	%rename("floating-schedule") 	floatingSchedule;
	%rename("ibor-index")           iborIndex;
    #endif
  public:
    %extend {
        static const IBFRSwap::Type Receiver = IBFRSwap::Receiver;
        static const IBFRSwap::Type Payer = IBFRSwap::Payer;
        IBFRSwapPtr(IBFRSwap::Type type, Real nominal,
                       const Date& startDate, 
					   const Period& swapTenor,
					   const Period& paymentTenor, 
					   Rate fixedRate,
                       Rate rateSpread,
                       const RepoChinaPtr& index) {
            boost::shared_ptr<RepoChina> libor =
                boost::dynamic_pointer_cast<RepoChina>(index);
            return new IBFRSwapPtr(
                    new IBFRSwap(type,nominal,startDate,swapTenor,
                                    paymentTenor,fixedRate,rateSpread,
                                    libor));
        }
        Rate fairRate() {
            return boost::dynamic_pointer_cast<IBFRSwap>(*self)->fairRate();
        }
        Spread fairRateSpread() {
            return boost::dynamic_pointer_cast<IBFRSwap>(*self)
                 ->fairRateSpread();
        }
        Real fixedLegBPS() {
            return boost::dynamic_pointer_cast<IBFRSwap>(*self)
                 ->fixedLegBPS();
        }
        Real floatingLegBPS() {
            return boost::dynamic_pointer_cast<IBFRSwap>(*self)
                 ->floatingLegBPS();
        }
		
		const Leg& fixedLeg() const {
		
			return boost::dynamic_pointer_cast<IBFRSwap>(*self)
				 ->fixedLeg();		
		}
		
		const Leg& floatingLeg() const {
		
			return boost::dynamic_pointer_cast<IBFRSwap>(*self)
				 ->floatingLeg();		
		}
		
		const Schedule& floatingSchedule() const {
			return boost::dynamic_pointer_cast<IBFRSwap>(*self)
				 ->floatingSchedule();				
		}
		
		const Schedule& fixedSchedule() const {
			return boost::dynamic_pointer_cast<IBFRSwap>(*self)
				 ->fixedSchedule();				
		}
		
		const boost::shared_ptr<IborIndex>& iborIndex() const {
			return boost::dynamic_pointer_cast<IBFRSwap>(*self)
				 ->iborIndex();				
		}
    }
};

%rename(DiscountingSwapEngine) DiscountingSwapEnginePtr;
class DiscountingSwapEnginePtr : public boost::shared_ptr<PricingEngine> {
  public:
    %extend {
        DiscountingSwapEnginePtr(
                            const Handle<YieldTermStructure>& discountCurve,
                            const Date& settlementDate = Date(),
                            const Date& npvDate = Date()) {
            return new DiscountingSwapEnginePtr(
                                    new DiscountingSwapEngine(discountCurve,
                                                              boost::none,
                                                              settlementDate,
                                                              npvDate));
        }
        DiscountingSwapEnginePtr(
                            const Handle<YieldTermStructure>& discountCurve,
                            bool includeSettlementDateFlows,
                            const Date& settlementDate = Date(),
                            const Date& npvDate = Date()) {
            return new DiscountingSwapEnginePtr(
                         new DiscountingSwapEngine(discountCurve,
                                                   includeSettlementDateFlows,
                                                   settlementDate,
                                                   npvDate));
        }
    }
};


%{
using QuantLib::AssetSwap;
typedef boost::shared_ptr<Instrument> AssetSwapPtr;
%}

%rename(AssetSwap) AssetSwapPtr;
class AssetSwapPtr : public SwapPtr {
    %feature("kwargs") AssetSwapPtr;
  public:
    %extend {
        AssetSwapPtr(bool payFixedRate,
                     const BondPtr& bond,
                     Real bondCleanPrice,
                     const InterestRateIndexPtr& index,
                     Spread spread,
                     const Schedule& floatSchedule = Schedule(),
                     const DayCounter& floatingDayCount = DayCounter(),
                     bool parAssetSwap = true) {
            const boost::shared_ptr<Bond> b =
                boost::dynamic_pointer_cast<Bond>(bond);
            const boost::shared_ptr<IborIndex> i =
                boost::dynamic_pointer_cast<IborIndex>(index);
            return new AssetSwapPtr(
                new AssetSwap(payFixedRate,b,bondCleanPrice,i,spread,
                              floatSchedule,floatingDayCount,parAssetSwap));
        }
        Real fairCleanPrice() {
            return boost::dynamic_pointer_cast<AssetSwap>(*self)
                ->fairCleanPrice();
        }
        Spread fairSpread() {
            return boost::dynamic_pointer_cast<AssetSwap>(*self)
                ->fairSpread();
        }
    }
};


#endif
