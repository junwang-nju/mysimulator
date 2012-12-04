
#ifndef _System_Interaction_Function_Pairwise_LJ1012_Pre_Name_H_
#define _System_Interaction_Function_Pairwise_LJ1012_Pre_Name_H_

#include "system/interaction/function/pairwise/pre-name.h"

namespace mysimulator {

  class PairLJ1012PreName : public PairwisePreName {

    public:

      static const unsigned int PairLJ1012NumberPre =
        PairwisePreName::PairwiseNumberPre;

  };

  const unsigned int PairLJ1012PreName::PairLJ1012NumberPre;

}

#endif

