
#ifndef _System_Interaction_Function_Pairwise_Harmonic_Vec_Name_H_
#define _System_Interaction_Function_Pairwise_Harmonic_Vec_Name_H_

#include "system/interaction/function/pairwise/vec-name.h"

namespace mysimulator {

  class PairHarmonicVecName : public PairwiseVecName {

    public:

      static const unsigned int PairHarmonicNumberVec =
        PairwiseVecName::PairwiseNumberVec;

  };

  const unsigned int PairHarmonicVecName::PairHarmonicNumberVec;

}

#endif

