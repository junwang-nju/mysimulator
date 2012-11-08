
#ifndef _System_Interaction_Parameter_Pairwise_LJ612_Interface_H_
#define _System_Interaction_Parameter_Pairwise_LJ612_Interface_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/parameter/pairwise/lj612/name.h"

namespace mysimulator {

  template <typename T>
  class PairLJ612Parameter {
    public:
      typedef PairLJ612Parameter<T>   Type;
      PairLJ612Parameter() = delete;
      PairLJ612Parameter(const Type&) = delete;
      Type& operator=(const Type&) = delete;
      ~PairLJ612Parameter() {}
  };

  template <typename T>
  class PairLJ612Parameter<Intrinsic<T>>
      : public InteractionParameter<Intrinsic<T>> {

    public:

      typedef PairLJ612Parameter<Intrinsic<T>>   Type;
      typedef InteractionParameter<Intrinsic<T>> ParentType;

      PairLJ612Parameter() : ParentType() {}
      PairLJ612Parameter(const Type& P) : ParentType(P) {}
      PairLJ612Parameter(Type&& P) : ParentType((ParentType&&)P) {}
      virtual ~PairLJ612Parameter() { ParentType::reset(); }

      Type& operator=(const Type& P) {
        ParentType::operator=(P);
        return *this;
      }

      virtual void allocate() override {
        ParentType::reset();
        this->_tag=InteractionName::PairLJ612;
        this->_FParam.allocate(PairLJ612ParameterName::NumberParameter);
      }

      virtual void build() override {
        assert((bool)(*this));
        assert(this->_FParam.size()>=
               PairLJ612ParameterName::NumberParameter);
        T tmd=this->_FParam[PairLJ612ParameterName::EqRadius];
        tmd*=tmd;
        T tmd1=tmd*tmd*tmd;
        tmd=tmd1*this->_FParam[PairLJ612ParameterName::EqEnergyDepth];
        T A=tmd*tmd1;
        T B=tmd+tmd;
        this->_FParam[PairLJ612ParameterName::FactorA]=A;
        this->_FParam[PairLJ612ParameterName::FactorB]=B;
        this->_FParam[PairLJ612ParameterName::DFactorA]=12*A;
        this->_FParam[PairLJ612ParameterName::DFactorB]=6*B;
      }

  };

}

#endif

