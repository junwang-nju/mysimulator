
#ifndef _System_Interaction_Parameter_Pairwise_LJ612_Interface_H_
#define _System_Interaction_Parameter_Pairwise_LJ612_Interface_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/parameter/pairwise/lj612/name.h"

namespace mysimulator {

  class PairLJ612Parameter : public InteractionParameter {

    public:

      typedef PairLJ612Parameter    Type;
      typedef InteractionParameter  ParentType;

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
        ParentType::_tag=InteractionName::PairLJ612;
        ParentType::_FParam.allocate(PairLJ612ParameterName::NumberParameter);
      }
      virtual void build() override {
        assert((bool)(*this));
        assert(ParentType::_FParam.size()>=
               PairLJ612ParameterName::NumberParameter);
        double tmd=ParentType::_FParam[PairLJ612ParameterName::EqRadius];
        tmd*=tmd;
        double tmd1=tmd*tmd*tmd;
        tmd=tmd1*ParentType::_FParam[PairLJ612ParameterName::EqEnergyDepth];
        double A=tmd*tmd1;
        double B=tmd+tmd;
        ParentType::_FParam[PairLJ612ParameterName::FactorA]  = A;
        ParentType::_FParam[PairLJ612ParameterName::FactorB]  = B;
        ParentType::_FParam[PairLJ612ParameterName::DFactorA] = 12*A;
        ParentType::_FParam[PairLJ612ParameterName::DFactorB] = 6*B;
      }

  };

}

#endif

