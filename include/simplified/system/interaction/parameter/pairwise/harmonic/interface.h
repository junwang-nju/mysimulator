
#ifndef _System_Interaction_Parameter_Pairwise_Harmonic_Interface_H_
#define _System_Interaction_Parameter_Pairwise_Harmonic_Interface_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/parameter/pairwise/harmonic/name.h"

namespace mysimulator {

  class PairHarmonicParameter : public InteractionParameter {

    public:

      typedef PairHarmonicParameter   Type;
      typedef InteractionParameter    ParentType;

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
        ParentType::_tag=InteractionName::PairHarmonic;
        ParentType::_FParam.allocate(
            PairHarmonicParameterName::NumberParameter);
      }
      virtual void build() override {
        assert((bool)(*this));
        assert(ParentType::_FParam.size()>=
               PairHarmonicParameterName::NumberParameter);
        ParentType::_FParam[PairHarmonicParameterName::DualEqStrength] =
          2 * ParentType::_FParam[PairHarmonicParameterName::EqStrength];
      }

  };

}

#endif

