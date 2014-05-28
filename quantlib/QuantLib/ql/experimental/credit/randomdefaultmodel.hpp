/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2008 Roland Lichters
 Copyright (C) 2009 Jose Aparicio

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

/*! \file randomdefaultmodel.hpp
    \brief Random default-time scenarios for a pool of credit names
*/

#ifndef quantlib_random_default_model_hpp
#define quantlib_random_default_model_hpp

#include <ql/math/randomnumbers/rngtraits.hpp>
#include <ql/experimental/credit/pool.hpp>
#include <ql/experimental/credit/onefactorcopula.hpp>
#include <ql/experimental/credit/defaultprobabilitykey.hpp>
#include <ql/math/solvers1d/brent.hpp>
#include <ql/instruments/bond.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <boost/make_shared.hpp>

namespace QuantLib {

    //! Base class for random default models
    /*! Provides sequences of random default times for each name in the pool. */
    class RandomDefaultModel : 
		public Observer, public Observable{
    public:
        RandomDefaultModel(boost::shared_ptr<Pool> pool,
                           const std::vector<boost::shared_ptr<DefaultProbKey> >& defaultKeys)
        : pool_(pool), defaultKeys_(defaultKeys) {
            // assuming none defaulted this is true.
            QL_REQUIRE(defaultKeys.size() == pool->size(),
                       "Incompatible pool and keys sizes.");
        }
        virtual ~RandomDefaultModel() {}
		void update() { notifyObservers(); }
        /*!
          Generate a sequence of random default times, one for each name in the
          pool, and store the result in the Pool using method setTime(name).
          tmax denotes the maximum relevant time- default times > tmax are not
          computed but set to tmax + 1 instead to save coputation time.
         */
        virtual void nextSequence() = 0;
		virtual const std::vector<Real>& determineDefaultTime(const std::vector<Real>& proSeq) const = 0; 
		virtual const std::vector<Real>& nextProbalilitySequence() = 0;
		std::vector<Real> defaultTimes(const std::vector<std::string>& referenceNames) const; 
		std::vector<Date> defaultDates(const std::vector<std::string>& referenceNames) const;
        virtual void reset() = 0;
		boost::shared_ptr<Pool> pool() const { return pool_;}
    protected:
        boost::shared_ptr<Pool> pool_;
        std::vector<boost::shared_ptr<DefaultProbKey> > defaultKeys_;
    };

    /*!
      Random default times using a one-factor Gaussian copula.
    */
    class GaussianRandomDefaultModel : public RandomDefaultModel {
    public:
        GaussianRandomDefaultModel(
                               boost::shared_ptr<Pool> pool,
                               const std::vector<boost::shared_ptr<DefaultProbKey> >& defaultKeys,
                               Handle<OneFactorCopula> copula,
                               Real accuracy, long seed, Real tmax = 3.0);
        void nextSequence();	
		const std::vector<Real>& nextProbalilitySequence();
		const std::vector<Real>& determineDefaultTime(const std::vector<Real>& proSeq) const; 
        void reset();
    private:
        Handle<OneFactorCopula> copula_;
        Real accuracy_;
        long seed_;
        PseudoRandom::rsg_type rsg_;
		CumulativeNormalDistribution dist_;
		std::vector<Handle<DefaultProbabilityTermStructure> > dts_;
		std::vector<Real> maxPros_;
		std::vector<std::string> names_;
		std::vector<Real> probSeq_;
		mutable std::vector<Real> defaultDates_;
		Real tmax_;
		Brent solver_;

    };

	class LoansPool {
	public:
		LoansPool(const std::vector<boost::shared_ptr<Bond> >& loansPortfolio)
			: loans_(loansPortfolio) {
				initiliaze();
		}

		const std::vector<boost::shared_ptr<Bond> >& loans() const {
			return loans_;
		}

		Size numberOfLoans() const {
			return loans_.size();
		}

		const Leg& loanCashflow(Size i) const {
			return loans_[i]->cashflows();
		}

		Leg couponCashFlow(Size i) const;

		Leg principleCashFlow(Size i) const;

		const std::vector<std::pair<Real,Date> >& plainLoanCashFlow(Size i) const {
			return generalCashFlows_[i];
		}

		const std::vector<std::pair<Real,Date> >& plainCouponCashFlow(Size i) const {
			return couponCashFlows_[i];
		}

		const std::vector<std::pair<Real,Date> >& plainPrincipleCashFlow(Size i) const {
			return principleCashFlows_[i];
		}

		const Leg& colletralCashFlow() const {
			return colletralCashFlow_;
		}

		const Leg& couponColletralCashFlow() const {
			return couponColletralCashFlow_;
		}

		const Leg& principleColletralCashFlow() const {
			return principleColletralCashFlow_;
		}

		Leg cashFlowAggregate(const std::vector<std::vector<std::pair<Real, Date> > >& loanLevelCashFlows) const;

	private:
		void initiliaze();
		
		std::vector<boost::shared_ptr<Bond> > loans_;
		std::vector<std::vector<std::pair<Real, Date> > > generalCashFlows_;
		std::vector<std::vector<std::pair<Real, Date> > > couponCashFlows_;
		std::vector<std::vector<std::pair<Real, Date> > > principleCashFlows_;

		Leg colletralCashFlow_;
		Leg couponColletralCashFlow_;
		Leg principleColletralCashFlow_;
	};

	class ColletralFlowGenerator {
	public:
		ColletralFlowGenerator(const LoansPool& loansPool,
							   Real survival= 0.5)
							   : loansPool_(loansPool), survival_(survival) {
			Leg colletralCashFlow = loansPool_.colletralCashFlow();

			for(Size i=0;i<colletralCashFlow.size();++i)
				wholePaymentDates_.push_back(colletralCashFlow[i]->date());

			Size poolSize = loansPool_.numberOfLoans();
			couponPaymentIndex_.resize(poolSize);
			principlePaymentIndex_.resize(poolSize);

			baseCouponCashFlows_ = std::vector<Real>(wholePaymentDates_.size(),0.0);
			basePrincipleCashFlows_ = std::vector<Real>(wholePaymentDates_.size(),0.0);

			for(Size i=0;i<poolSize;++i) {
				const std::vector<std::pair<Real,Date> >& couponLeg = loansPool_.plainCouponCashFlow(i);
				Size startLoop = 0;
				for(Size k=0;k<couponLeg.size();++k) {
					while(wholePaymentDates_[startLoop]!=couponLeg[k].second)
						++startLoop;
					couponPaymentIndex_[i].push_back(startLoop);
					baseCouponCashFlows_[startLoop] += couponLeg[k].first;
				}

				const std::vector<std::pair<Real,Date> >& principleLeg = loansPool_.plainPrincipleCashFlow(i);
				startLoop = 0;
				for(Size k=0;k<principleLeg.size();++k) {
					while(wholePaymentDates_[startLoop]!=principleLeg[k].second)
						++startLoop;
					principlePaymentIndex_[i].push_back(startLoop);
					basePrincipleCashFlows_[startLoop] += principleLeg[k].first;
				}
			}

			//colletralCashFlows_ = std::vector<Real>(wholePaymentDates_.size(),0.0);
			couponCashFlows_ = std::vector<Real>(wholePaymentDates_.size(),0.0);
			principleCashFlows_ = std::vector<Real>(wholePaymentDates_.size(),0.0);

			for(Size k=0;k<wholePaymentDates_.size();++k) {
				cashFlowLegs_.first.push_back(boost::make_shared<SimpleCashFlow>(0.0, wholePaymentDates_[k]));
				cashFlowLegs_.second.push_back(boost::make_shared<SimpleCashFlow>(0.0, wholePaymentDates_[k]));
			}
		}

		const std::pair<Leg, Leg>& simulatingOnePath(const std::vector<Real>& defaultDates, Frequency freq = Monthly) const;

	private:

		Leg aggregateCashFlows(const Leg& rawCashFlows, Frequency freq) const;

		Real survival_;
		const LoansPool& loansPool_;
		std::vector<Date> wholePaymentDates_;
		std::vector<std::vector<Size> > couponPaymentIndex_;
		std::vector<std::vector<Size> > principlePaymentIndex_;
		//mutable std::vector<Real> colletralCashFlows_;
		mutable std::vector<Real> couponCashFlows_;
		mutable std::vector<Real> principleCashFlows_;
		std::vector<Real> baseCouponCashFlows_;
		std::vector<Real> basePrincipleCashFlows_;
		mutable std::pair<Leg, Leg> cashFlowLegs_;
		mutable std::pair<Leg, Leg> aggregatedCashFlows_;
	};

}

#endif
