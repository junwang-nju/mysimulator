
#ifndef _System_Interaction_Function_Pairwise_Core12_Vec_Name_H_
#define _System_Interaction_Function_Pairwise_Core12_Vec_Name_H_

#include "system/interaction/function/pairwise/vec-name.h"

namespace mysimulator {

  class PairCore12VecName : public PairwiseVecName {

    public:

      static const unsigned int PairCore12NumberVec =
        PairwiseVecName::PairwiseNumberVec;

  };

  const unsigned int PairCore12VecName::PairCore12NumberVec;

}

#endif

