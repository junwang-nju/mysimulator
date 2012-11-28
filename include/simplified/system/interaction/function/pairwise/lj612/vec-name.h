
#ifndef _System_Interaction_Function_Pairwise_LJ612_Vec_Name_H_
#define _System_Interaction_Function_Pairwise_LJ612_Vec_Name_H_

#include "system/interaction/function/pairwise/vec-name.h"

namespace mysimulator {

  class PairLJ612VecName : public PairwiseVecName {

    public:

      static const unsigned int PairLJ612NumberVec =
        PairwiseVecName::PairwiseNumberVec;

  };

  const unsigned int PairLJ612VecName::PairLJ612NumberVec;

}

#endif

