
#ifndef _System_Interaction_Parameter_Pairwise_Harmonic_Interface_H_
#define _System_Interaction_Parameter_Pairwise_Harmonic_Interface_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/parameter/pairwise/harmonic/name.h"

namespace mysimulator {

  template <typename T=Double>
  class PairHarmonicParameter {
    public:
      typedef PairHarmonicParameter<T>  Type;
      PairHarmonicParameter() = delete;
      PairHarmonicParameter(const Type&) = delete;
      Type& operator=(const Type&) = delete;
      ~PairHarmonicParameter() {}
  };

  template <typename T>
  class PairHarmonicParameter<Intrinsic<T>>
      : public InteractionParameter<Intrinsic<T>> {

    public:

      typedef PairHarmonicParameter<Intrinsic<T>>  Type;
      typedef InteractionParameter<Intrinsic<T>>   ParentType;

      PairHarmonicParameter() : ParentType() {}
      PairHarmonicParameter(const Type& P) : ParentType(P) {}
      PairHarmonicParameter(Type&& P) : ParentType((ParentType&&)P) {}
      virtual ~PairHarmonicParameter() { ParentType::reset(); }

      Type& operator=(const Type& P) {
        ParentType::operator=(P);
        return *this;
      }

      virtual void allocate() override {
        ParentType::reset();
        this->_tag=InteractionName::PairHarmonic;
        this->_FParam.allocate(PairHarmonicParameterName::NumberParameter);
      }
      virtual void build() override {
        assert((bool)(*this));
        assert(this->_FParam.size()>=
               PairHarmonicParameterName::NumberParameter);
        this->_FParam[PairHarmonicParameterName::DualEqStrength] =
          2*this->_FParam[PairHarmonicParameterName::EqStrength];
      }

  };

}

#endif

