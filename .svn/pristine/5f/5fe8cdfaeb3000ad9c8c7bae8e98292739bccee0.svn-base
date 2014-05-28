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

#include <ql/experimental/credit/randomdefaultmodel.hpp>
#include <algorithm>


using namespace std;

namespace QuantLib {

    namespace {

        // Utility for the numerical solver
        class Root {
          public:
            Root(const Handle<DefaultProbabilityTermStructure> dts, Real pd)
            : dts_(dts), pd_(pd) {}
            Real operator()(Real t) const {
                QL_REQUIRE (t >= 0.0, "t < 0");
                return dts_->defaultProbability(t, true) - pd_;
            }
          private:
            const Handle<DefaultProbabilityTermStructure> dts_;
            Real pd_;
        };

		boost::shared_ptr<CashFlow> helperForCashFlows(const std::pair<Date,Real>& cashflow) {
			return boost::make_shared<SimpleCashFlow>(cashflow.second, cashflow.first);
		}

		boost::shared_ptr<CashFlow> helperForCashFlows2(const std::pair<Real,Date>& cashflow) {
			return boost::make_shared<SimpleCashFlow>(cashflow.first, cashflow.second);
		}

    }
	

	std::vector<Real> RandomDefaultModel::defaultTimes(const std::vector<std::string>& referenceNames) const {
		std::vector<Real> res(referenceNames.size());
		for(Size i=0;i<res.size();++i) {
			res[i] = pool_->getTime(referenceNames[i]);
		}
		return res;
	}

	std::vector<Date> RandomDefaultModel::defaultDates(const std::vector<std::string>& referenceNames) const {
		std::vector<Date> res(referenceNames.size());
		for(Size i=0;i<res.size();++i) {
			res[i] = pool_->getDate(referenceNames[i]);
		}
		return res;
	}

    GaussianRandomDefaultModel::GaussianRandomDefaultModel(
                               boost::shared_ptr<Pool> pool,
                               const std::vector<boost::shared_ptr<DefaultProbKey> >& defaultKeys,
                               Handle<OneFactorCopula> copula,
                               Real accuracy,
                               long seed,
							   Real tmax)
        : RandomDefaultModel(pool, defaultKeys),
          copula_(copula),
          accuracy_(accuracy),
          seed_(seed),
          rsg_(PseudoRandom::make_sequence_generator(pool->size()+1, seed)),
	      defaultDates_(pool->size()),
	      tmax_(tmax) {
			  registerWith(copula);
			  names_ = pool_->names();
			  for (Size j = 0; j < pool_->size(); j++) {
				  const string name = names_[j];
				  const Handle<DefaultProbabilityTermStructure>&
					  dt = pool_->get(name).defaultProbability(*(defaultKeys_[j]));
				  dts_.push_back(dt);
				  maxPros_.push_back(dt->defaultProbability(tmax));
			  }
	}

    void GaussianRandomDefaultModel::reset() {
        Size dim = pool_->size() + 1;
        rsg_ = PseudoRandom::make_sequence_generator(dim, seed_);
    }

    void GaussianRandomDefaultModel::nextSequence() {
        const std::vector<Real>& values = nextProbalilitySequence();
		const Date& refDate = Settings::instance().evaluationDate();
        for (Size j = 0; j < pool_->size(); j++) {
			const Real p = values[j];
            if (maxPros_[j] < p)
				pool_->setTime(names_[j], tmax_+1, dts_[j]->dayCounter(), refDate);
			else
				pool_->setTime(names_[j], solver_.solve(Root(dts_[j],p),accuracy_,0,1), dts_[j]->dayCounter(), refDate);
        }
    }

	const std::vector<Real>& GaussianRandomDefaultModel::determineDefaultTime(const std::vector<Real>& proSeq) const {;
		for (Size j = 0; j < pool_->size(); ++j) {
			const Real p = proSeq[j];
			if (maxPros_[j] < p)
				defaultDates_[j] = tmax_+1;
			else
				defaultDates_[j] = solver_.solve(Root(dts_[j],p),accuracy_,0,1);
		}
		return defaultDates_;
	}

	const std::vector<Real>& GaussianRandomDefaultModel::nextProbalilitySequence(){
		const std::vector<Real>& values = rsg_.nextSequence().value;
		probSeq_.resize(values.size()-1);
		const Real a = sqrt(copula_->correlation());
		const Real tmp = sqrt(1.0-a*a);
		for (Size j = 0; j < pool_->size(); j++) {
			const Real y = a * values[0] + tmp * values[j+1];
			probSeq_[j] = dist_(y);
		}
		return probSeq_;
	}


	void LoansPool::initiliaze() {
		Size poolSize = loans_.size();
		couponCashFlows_.resize(poolSize);
		principleCashFlows_.resize(poolSize);
		generalCashFlows_.resize(poolSize);

		for(Size i=0;i<poolSize;++i) {
			Leg cashFlow = loans_[i]->cashflows();
			bool isAmortizing = loans_[i]->redemptions().size() != 1;
			if(!isAmortizing) {
				for(Size k=0;k<cashFlow.size()-1;++k)
				{
					couponCashFlows_[i].push_back(make_pair<Real, Date>(cashFlow[k]->amount(),cashFlow[k]->date()));
					generalCashFlows_[i].push_back(make_pair<Real, Date>(cashFlow[k]->amount(),cashFlow[k]->date()));
				}
				principleCashFlows_[i].push_back(make_pair<Real, Date>(cashFlow[cashFlow.size()-1]->amount(), cashFlow[cashFlow.size()-1]->date()));
				generalCashFlows_[i].push_back(make_pair<Real, Date>(cashFlow[cashFlow.size()-1]->amount(), cashFlow[cashFlow.size()-1]->date()));
			} else {
				for(Size k=0;k<cashFlow.size();k+=2) {
					couponCashFlows_[i].push_back(make_pair<Real, Date>(cashFlow[k]->amount(),cashFlow[k]->date()));
					generalCashFlows_[i].push_back(make_pair<Real, Date>(cashFlow[k]->amount(),cashFlow[k]->date()));
				}
				for(Size k=1;k<cashFlow.size();k+=2) {
					principleCashFlows_[i].push_back(make_pair<Real, Date>(cashFlow[k]->amount(),cashFlow[k]->date()));
					generalCashFlows_[i].push_back(make_pair<Real, Date>(cashFlow[k]->amount(),cashFlow[k]->date()));
				}
			}
		}

		colletralCashFlow_ = cashFlowAggregate(generalCashFlows_);
		couponColletralCashFlow_ = cashFlowAggregate(couponCashFlows_);
		principleColletralCashFlow_ = cashFlowAggregate(principleCashFlows_);
	}

	Leg LoansPool::cashFlowAggregate(const std::vector<std::vector<std::pair<Real, Date> > >& loanLevelCashFlows) const {
		std::map<Date, Real> colletralCashFlows;
		Leg res;
		Size poolSize = loanLevelCashFlows.size();
		for(Size j=0; j<poolSize; ++j) {
			for(Size k=0; k < loanLevelCashFlows[j].size(); ++k) {
				Date key = loanLevelCashFlows[j][k].second;
				if(colletralCashFlows.find(key) != colletralCashFlows.end()) 
					colletralCashFlows[key] += loanLevelCashFlows[j][k].first;
				else
					colletralCashFlows[key] = loanLevelCashFlows[j][k].first;
			}
		}

		std::transform(colletralCashFlows.begin(), colletralCashFlows.end(), std::back_inserter(res), &helperForCashFlows);
		return res;
	}

	Leg LoansPool::couponCashFlow(Size i) const {
		Leg res;
		std::transform(couponCashFlows_[i].begin(), couponCashFlows_[i].end(), std::back_inserter(res), &helperForCashFlows2);
		return res;
	}

	Leg LoansPool::principleCashFlow(Size i) const {
		Leg res;
		std::transform(principleCashFlows_[i].begin(), principleCashFlows_[i].end(), std::back_inserter(res), &helperForCashFlows2);
		return res;
	}

	const std::pair<Leg, Leg>& ColletralFlowGenerator::simulatingOnePath(const std::vector<Real>& defaultDates, Frequency freq) const{
		Size poolSize = loansPool_.numberOfLoans();
		
		//colletralCashFlows_.assign(colletralCashFlows_.size(),0.0);
		couponCashFlows_ = baseCouponCashFlows_;
		principleCashFlows_ = basePrincipleCashFlows_;

		const Date& refDate = Settings::instance().evaluationDate();

		for(Size i=0;i<poolSize;++i) {

			const Real& defaultTime = defaultDates[i];
			const Date& defaultDate = refDate + int(defaultTime*365+0.5) * Days;
			const std::vector<std::pair<Real,Date> >& coupons
				= loansPool_.plainCouponCashFlow(i);

			for(int k = coupons.size()-1; k>=0; --k) {
				const Date& key = coupons[k].second;
				if(key >= defaultDate) {
					//colletralCashFlows_[index] += amount;
					const Size& index = couponPaymentIndex_[i][k];
					couponCashFlows_[index] -= coupons[k].first;
				} else {
					break;
				}
			}

			// Find the nearest index at which bond default
			Size nearestIndex = 0;
			for(int k=wholePaymentDates_.size()-1;k>=0;--k) {
				if(wholePaymentDates_[k] <= defaultDate) {
					nearestIndex = k;
					break;
				}
			}

			const std::vector<std::pair<Real,Date> >& principles
				= loansPool_.plainPrincipleCashFlow(i);

			for(int k=principles.size()-1; k>=0; --k) {
				const Date& key = principles[k].second;		
				if(key >= defaultDate) {
					//colletralCashFlows_[index] += amount;
					const Size& index = principlePaymentIndex_[i][k];
					principleCashFlows_[index] -= principles[k].first;
					principleCashFlows_[nearestIndex] += principles[k].first * survival_;
				}
				else {
					break;
				}
			}
		}

		
		for(Size k=0;k<wholePaymentDates_.size();++k) {
			cashFlowLegs_.first[k]->setAmount(couponCashFlows_[k]);
			cashFlowLegs_.second[k]->setAmount(principleCashFlows_[k]);
		}

		aggregatedCashFlows_.first =  aggregateCashFlows(cashFlowLegs_.first, freq);
		aggregatedCashFlows_.second =  aggregateCashFlows(cashFlowLegs_.second, freq);
		return aggregatedCashFlows_;

	}

	Leg ColletralFlowGenerator::aggregateCashFlows(const Leg& rawCashFlows, Frequency freq) const {
		QL_REQUIRE(rawCashFlows.size()>=1, "Cash flow size should at least be 1");
		if(freq == Daily)
			return rawCashFlows;	
		Date firstDate = rawCashFlows[0]->date();
		Date lastDate = rawCashFlows[rawCashFlows.size()-1]->date();

		Date startEnd = firstDate;
		Date lastEnd = firstDate;

		if(freq<=Monthly) {
			startEnd = Date::endOfMonth(firstDate);
			lastEnd = Date::endOfMonth(lastDate);
		} else {
			startEnd = Date::nextWeekday(firstDate, Friday);
			lastEnd = Date::nextWeekday(lastDate, Friday);
		}

		std::vector<Date> pillarDates;
		Leg tmpLeg;
		while(lastEnd>=startEnd) {
			tmpLeg.push_back(boost::make_shared<SimpleCashFlow>(0.0,startEnd));
			pillarDates.push_back(startEnd);
			startEnd += Period(freq);
			if(freq<=Monthly) {
				startEnd = Date::endOfMonth(startEnd);
			} 
		}

		if((*(tmpLeg.end()-1))->date() < lastEnd) {
			tmpLeg.push_back(boost::make_shared<SimpleCashFlow>(0.0,lastEnd));
			pillarDates.push_back(lastEnd);
		}

		Size startCount = 0;

		for(Size i=0; i<rawCashFlows.size();++i) {
			const Date& key = rawCashFlows[i]->date();
			const Real& amount = rawCashFlows[i]->amount();

			if(key<=pillarDates[startCount]) {
				tmpLeg[startCount]->setAmount(amount + tmpLeg[startCount]->amount());
			} else {
				while(pillarDates[startCount]<key)
					++startCount;
				tmpLeg[startCount]->setAmount(amount + tmpLeg[startCount]->amount());
			}
		}

		return tmpLeg;
	}
}

