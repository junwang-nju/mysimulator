
#ifndef _System_Interaction_Function_Pairwise_LJ612Cut_Vec_Name_H_
#define _System_Interaction_Function_Pairwise_LJ612Cut_Vec_Name_H_

#include "system/interaction/function/pairwise/vec-name.h"

namespace mysimulator {

  class PairLJ612CutVecName : public PairwiseVecName {

    public:

      static const unsigned int PairLJ612CutNumberVec =
        PairwiseVecName::PairwiseNumberVec;

  };

  const unsigned int PairLJ612CutVecName::PairLJ612CutNumberVec;

}

#endif

