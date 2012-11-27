
#ifndef _System_Interaction_Function_Pairwise_Harmonic_Pre_Name_H_
#define _System_Interaction_Function_Pairwise_Harmonic_Pre_Name_H_

#include "system/interaction/function/pairwise/pre-name.h"

namespace mysimulator {

  class PairHarmonicPreName : public PairwisePreName {

    public:

      static const unsigned int PairHarmonicNumberPre =
        PairwisePreName::PairwiseNumberPre;
  };

  const unsigned int PairHarmonicPreName::PairHarmonicNumberPre;

}

#endif

