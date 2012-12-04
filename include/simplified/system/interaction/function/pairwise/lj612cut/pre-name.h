
#ifndef _System_Interaction_Function_Pairwise_LJ612Cut_Pre_Name_H_
#define _System_Interaction_Function_Pairwise_LJ612Cut_Pre_Name_H_

#include "system/interaction/function/pairwise/pre-name.h"

namespace mysimulator {

  class PairLJ612CutPreName : public PairwisePreName {

    public:

      static const unsigned int PairLJ612CutNumberPre =
        PairwisePreName::PairwiseNumberPre;

  };

  const unsigned int PairLJ612CutPreName::PairLJ612CutNumberPre;

}

#endif

