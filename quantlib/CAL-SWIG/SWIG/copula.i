#ifndef quantlib_copula_i
#define quantlib_copula_i

%include common.i
%include types.i
%include observer.i
%include defaultprobability.i
%include currencies.i
%include date.i
%include vectors.i
%include <std_pair.i>
%include bonds.i

%{
    using QuantLib::OneFactorCopula;
%}

%ignore OneFactorCopula;
class OneFactorCopula {
    #if defined(SWIGMZSCHEME) || defined(SWIGGUILE)
    %rename("cumulative-z")              cumulativeZ;
    %rename("cumulative-y")              cumulativeY;
    %rename("inverse-cumulative-y")      inverseCumulativeY;
    %rename("conditional-probability")   conditionalProbability;
    %rename("check-moments")             zeroRate;
    #endif

  public:
    Real density(Real m) const;
    Real cumulativeZ(Real z) const;
    Real cumulativeY(Real y) const;
    Real inverseCumulativeY(Real p) const;
    Real correlation() const;
    Real conditionalProbability(Real prob, Real m) const;
    std::vector<Real> conditionalProbability(const std::vector<Real>& prob,
                                                 Real m) const;
    Real integral(Real p) const;
    int checkMoments(Real tolerance) const;
};

%template(OneFactorCopula) boost::shared_ptr<OneFactorCopula>;
IsObservable(boost::shared_ptr<OneFactorCopula>);

%template(OneFactorCopulaHandle) Handle<OneFactorCopula>;
IsObservable(Handle<OneFactorCopula>);
%template(RelinkableOneFactorCopulaeHandle)
RelinkableHandle<OneFactorCopula>;

%{
using QuantLib::OneFactorGaussianCopula;
using QuantLib::OneFactorStudentCopula;
typedef boost::shared_ptr<OneFactorCopula> OneFactorGaussianCopulaPtr;
typedef boost::shared_ptr<OneFactorCopula> OneFactorStudentCopulaPtr;
%}

%rename(OneFactorGaussianCopula) OneFactorGaussianCopulaPtr;
class OneFactorGaussianCopulaPtr: public boost::shared_ptr<OneFactorCopula> {
  public:
    %extend {
        OneFactorGaussianCopulaPtr(const Handle<Quote>& correlation,
                                   Real maximum = 5, Size integrationSteps = 50) {
            return new OneFactorGaussianCopulaPtr(
                new OneFactorGaussianCopula(correlation, maximum, integrationSteps));
        }
    }

}; 


%rename(OneFactorStudentCopula) OneFactorStudentCopulaPtr;
class OneFactorStudentCopulaPtr: public boost::shared_ptr<OneFactorCopula> {
  public:
    %extend {
        OneFactorStudentCopulaPtr(const Handle<Quote>& correlation,
                                int nz, int nm,
                                Real maximum = 10, Size integrationSteps = 200) {
            return new OneFactorStudentCopulaPtr(
                new OneFactorStudentCopula(correlation, nz, nm, maximum, integrationSteps));
        }
    }
};

%{
    using QuantLib::DefaultProbKey;
    using QuantLib::Issuer;
    using QuantLib::Pool;
    using QuantLib::Seniority;
    using QuantLib::SecDom;
    using QuantLib::SnrFor;
    using QuantLib::SubLT2;
    using QuantLib::JrSubT2;
    using QuantLib::PrefT1;
    using QuantLib::NoSeniority;
    using QuantLib::AtomicDefault;
    using QuantLib::Restructuring;
    using QuantLib::DefaultType;
    using QuantLib::DefaultEvent;
    typedef boost::shared_ptr<Pool> PoolPtr;
%}


%ignore DefaultProbKey;
class DefaultProbKey {

};

enum Seniority {
    SecDom = 0,
    SnrFor = 1,
    SubLT2 = 2,
    JrSubT2 = 3,
    PrefT1 = 4,
    NoSeniority = 5
};

class AtomicDefault {
public:
   enum Type {
      Restructuring = 0,
      Bankruptcy = 1,
      FailureToPay = 2,
      RepudiationMoratorium = 3,
      Acceleration = 4,
      Default = 5,
      Downgrade = 6,
      MergerEvent = 7
   };
};

class Restructuring {
public:
   enum Type {
      NoRestructuring = 0,
      ModifiedRestructuring = 1,
      ModifiedModifiedRestructuring = 2,
      FullRestructuring = 3,
      AnyRestructuring = 4
   };
};

%ignore DefaultType;
class DefaultType {
public:
    DefaultType(AtomicDefault::Type defType = AtomicDefault::Bankruptcy,
                Restructuring::Type restType = Restructuring::NoRestructuring);
};

%template(DefaultType) boost::shared_ptr<DefaultType>;


#if defined(SWIGCSHARP)
SWIG_STD_VECTOR_ENHANCED( boost::shared_ptr<DefaultType> )
#endif
%template(DefaultTypeVec) std::vector<boost::shared_ptr<DefaultType> >;
typedef std::vector<boost::shared_ptr<DefaultType> > DefaultTypeVec;

#if defined(SWIGCSHARP)
SWIG_STD_VECTOR_ENHANCED( Handle<DefaultProbabilityTermStructure> )
#endif
%template(DefaultProbabilityTermStructureVec) std::vector<Handle<DefaultProbabilityTermStructure> >;
typedef std::vector<Handle<DefaultProbabilityTermStructure> > DefaultProbabilityTermStructureVec;

%{
  typedef std::vector<Handle<DefaultProbabilityTermStructure> > DefaultProbabilityTermStructureVec;
%}

%ignore DefaultEvent;
class DefaultEvent {
public:
    DefaultEvent(const Date& creditEventDate,
                     const DefaultType& atomicEvType,
                     const Currency& curr,
                     Seniority bondsSen,
                     const Date& settleDate = Null<Date>(),
                     Real recoveryRate = 0.4);
};

%template(DefaultEvent) boost::shared_ptr<DefaultEvent>;

%template(key_curve_pair) std::pair<boost::shared_ptr<DefaultProbKey>,Handle<DefaultProbabilityTermStructure> >;
typedef std::pair<boost::shared_ptr<DefaultProbKey>,Handle<DefaultProbabilityTermStructure> > key_curve_pair;

%template(key_curve_pair_vec) std::vector<std::pair<boost::shared_ptr<DefaultProbKey>,Handle<DefaultProbabilityTermStructure> > >;
typedef std::vector<std::pair<boost::shared_ptr<DefaultProbKey>,Handle<DefaultProbabilityTermStructure> > > key_curve_pair_vec;

%{
  typedef std::pair<boost::shared_ptr<DefaultProbKey>,Handle<DefaultProbabilityTermStructure> > key_curve_pair;
  typedef std::vector<std::pair<boost::shared_ptr<DefaultProbKey>,Handle<DefaultProbabilityTermStructure> > > key_curve_pair_vec;
%}

class Issuer {
public:
    Issuer(const key_curve_pair_vec& probabilities);
};


%template(IssuerVec) std::vector<Issuer>;
typedef std::vector<Issuer> IssuerVec;

%{
  typedef std::vector<Issuer> IssuerVec;
%}

%rename(Pool) PoolPtr;
class PoolPtr {
    #if defined(SWIGMZSCHEME) || defined(SWIGGUILE)
    %rename("set-time")  setTime;
    %rename("get-time")  getTime;
    #endif
  public:
    %extend {
      PoolPtr() {
        return new PoolPtr(new Pool());
      }
      Size size() const {
        return boost::dynamic_pointer_cast<Pool>(*self)
                ->size(); 
      }
      void clear() {
        boost::dynamic_pointer_cast<Pool>(*self)
                ->clear(); 
      }
      bool has (const std::string& name) const {
        return boost::dynamic_pointer_cast<Pool>(*self)
                ->has(name); 
      }
      void add (const std::string& name, const Issuer& issuer) {
        boost::dynamic_pointer_cast<Pool>(*self)
                ->add(name, issuer);
      }
      const Issuer& get (const std::string& name) const {
        return boost::dynamic_pointer_cast<Pool>(*self)
                ->get(name);
      }
      void setTime(const std::string& name, Real time, const DayCounter& dc, Date refDate = Date()) {
        boost::dynamic_pointer_cast<Pool>(*self)
                ->setTime(name, time, dc, refDate);
      }
      Real getTime (const std::string& name) const {
        return boost::dynamic_pointer_cast<Pool>(*self)
                ->getTime(name);
      }
      Date getDate(const std::string& name) const {
        return boost::dynamic_pointer_cast<Pool>(*self)
                ->getDate(name);
      }
      const std::vector<std::string>& names() const {
        return boost::dynamic_pointer_cast<Pool>(*self)
                ->names();
      }
  }
};

%{
    using QuantLib::DefaultProbKey;
    using QuantLib::NorthAmericaCorpDefaultKey;
    using QuantLib::RandomDefaultModel;
    using QuantLib::GaussianRandomDefaultModel;
    typedef boost::shared_ptr<DefaultProbKey> NorthAmericaCorpDefaultKeyPtr;
    typedef boost::shared_ptr<RandomDefaultModel> RandomDefaultModelPtr;
    typedef boost::shared_ptr<RandomDefaultModel> GaussianRandomDefaultModelPtr;
%}

%ignore DefaultProbKey;
class DefaultProbKey {
public:
    DefaultProbKey(const DefaultTypeVec& eventTypes,
                       const Currency cur,
                       Seniority sen);
    const Currency& currency() const;
    Seniority seniority() const;
    const DefaultTypeVec& eventTypes() const;
    Size size() const;
};

%template(DefaultProbKey) boost::shared_ptr<DefaultProbKey>;

%template(DefaultProbKeyVec) std::vector<boost::shared_ptr<DefaultProbKey> >;
typedef std::vector<boost::shared_ptr<DefaultProbKey> > DefaultProbKeyVec;

%{
  typedef std::vector<boost::shared_ptr<DefaultProbKey> > DefaultProbKeyVec;;
%}

%rename(NorthAmericaCorpDefaultKey) NorthAmericaCorpDefaultKeyPtr;
class NorthAmericaCorpDefaultKeyPtr: public boost::shared_ptr<DefaultProbKey> {
  public:
    %extend {
        NorthAmericaCorpDefaultKeyPtr(const Currency& currency,
                                   Seniority sen,
                                   Period graceFailureToPay = Period(30, Days),
                                   Real amountFailure = 1.e6) {
            return new NorthAmericaCorpDefaultKeyPtr(
                new NorthAmericaCorpDefaultKey(currency, sen, graceFailureToPay, amountFailure));
        }
    }
};


%rename(RandomDefaultModel) RandomDefaultModelPtr;
class RandomDefaultModelPtr {
    #if defined(SWIGMZSCHEME) || defined(SWIGGUILE)
    %rename("default-times")  defaultTimes;
    %rename("default-dates")  defaultDates;
    #endif
public:
  %extend {
      void nextSequence() {
        boost::dynamic_pointer_cast<RandomDefaultModel>(*self)
                ->nextSequence();
      }
      void reset() {
        boost::dynamic_pointer_cast<RandomDefaultModel>(*self)
                ->reset();
      }
      PoolPtr pool() const {
        return boost::dynamic_pointer_cast<RandomDefaultModel>(*self)->pool();
      }
      const std::vector<Real>& nextProbalilitySequence() {
        return boost::dynamic_pointer_cast<RandomDefaultModel>(*self)
                ->nextProbalilitySequence();
      }
      const std::vector<Real>& determineDefaultTime(const std::vector<Real>& proSeq) const {
        return boost::dynamic_pointer_cast<RandomDefaultModel>(*self)
                ->determineDefaultTime(proSeq);
      }
      std::vector<Real> defaultTimes(const std::vector<std::string>& referenceNames) const {
        return boost::dynamic_pointer_cast<RandomDefaultModel>(*self)->defaultTimes(referenceNames);
      }
      std::vector<Date> defaultDates(const std::vector<std::string>& referenceNames) const {
        return boost::dynamic_pointer_cast<RandomDefaultModel>(*self)->defaultDates(referenceNames);
      }
    }
};

%rename(GaussianRandomDefaultModel) GaussianRandomDefaultModelPtr;
class GaussianRandomDefaultModelPtr: public RandomDefaultModelPtr {
  public:
    %extend {
        GaussianRandomDefaultModelPtr(const PoolPtr& pool,
                                      const DefaultProbKeyVec& defaultKeys,
                                      Handle<OneFactorCopula> copula,
                                      Real accuracy = 1e-5, long seed = 42, Real tmax = 3.0) {
            return new GaussianRandomDefaultModelPtr(
                new GaussianRandomDefaultModel(boost::dynamic_pointer_cast<Pool>(pool), defaultKeys, copula, accuracy, seed, tmax));
        }
    }
};

%{
    using QuantLib::LoansPool;
    using QuantLib::ColletralFlowGenerator;
    typedef boost::shared_ptr<LoansPool> LoansPoolPtr;
    typedef boost::shared_ptr<ColletralFlowGenerator> ColletralFlowGeneratorPtr;
%}

%rename(LoansPool) LoansPoolPtr;
class LoansPoolPtr {
    #if defined(SWIGMZSCHEME) || defined(SWIGGUILE)
    %rename("number-loans")              numberOfLoans;
    #endif

  public:
    %extend {
      LoansPoolPtr(const std::vector<boost::shared_ptr<Instrument> >& loansPortfolio) {
        std::vector<boost::shared_ptr<Bond> > rawPool;
        for(Size i=0;i<loansPortfolio.size();++i) {
          rawPool.push_back(boost::dynamic_pointer_cast<Bond>(loansPortfolio[i]));
        }

        return new LoansPoolPtr(new LoansPool(rawPool));
      }
      Size numberOfLoans() const {
        return boost::dynamic_pointer_cast<LoansPool>(*self)->numberOfLoans();
      }
    }
};

%template(cash_flow_pair) std::pair<Leg, Leg>;
typedef std::pair<Leg, Leg> cash_flow_pair;

%{
  typedef std::pair<Leg, Leg> cash_flow_pair;
%}

%rename(ColletralFlowGenerator) ColletralFlowGeneratorPtr;
class ColletralFlowGeneratorPtr {

  public:
    %extend {
      ColletralFlowGeneratorPtr(const LoansPoolPtr& loansPool, Real survival = 0.5) {
        return new ColletralFlowGeneratorPtr(new ColletralFlowGenerator(*boost::dynamic_pointer_cast<LoansPool>(loansPool), survival));
      }
      const cash_flow_pair& simulatingOnePath(const std::vector<Real>& defaultDates, Frequency freq = Monthly) const {
        return boost::dynamic_pointer_cast<ColletralFlowGenerator>(*self)->simulatingOnePath(defaultDates, freq);
      }
    }
};

#endif