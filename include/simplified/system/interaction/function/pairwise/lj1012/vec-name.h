
#ifndef _System_Interaction_Function_Pairwise_LJ1012_Vec_Name_H_
#define _System_Interaction_Function_Pairwise_LJ1012_Vec_Name_H_

#include "system/interaction/function/pairwise/vec-name.h"

namespace mysimulator {

  class PairLJ1012VecName : public PairwiseVecName {

    public:

      static const unsigned int PairLJ1012NumberVec =
        PairwiseVecName::PairwiseNumberVec;

  };

  const unsigned int PairLJ1012VecName::PairLJ1012NumberVec;

}

#endif

