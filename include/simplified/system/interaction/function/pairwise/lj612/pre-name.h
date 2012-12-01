
#ifndef _System_Interaction_Function_Pairwise_LJ612_Pre_Name_H_
#define _System_Interaction_Function_Pairwise_LJ612_Pre_Name_H_

#include "system/interaction/function/pairwise/pre-name.h"

namespace mysimulator {

  class PairLJ612PreName : public PairwisePreName {

    public:

      static const unsigned int PairLJ612NumberPre =
        PairwisePreName::PairwiseNumberPre;

  };

  const unsigned int PairLJ612PreName::PairLJ612NumberPre;

}

#endif
