
#ifndef _System_Interaction_Function_Pairwise_LJ612Cut_Post_Name_H_
#define _System_Interaction_Function_Pairwise_LJ612Cut_Post_Name_H_

#include "system/interaction/function/pairwise/lj612/post-name.h"

namespace mysimulator {

  class PairLJ612CutPostName {

    public:

      static const unsigned int PairLJ612CutIvDistanceSQ
        = PairLJ612PostName::PairLJ612IvDistanceSQ;
      static const unsigned int PairLJ612CutIvDistance6
        = PairLJ612PostName::PairLJ612IvDistance6;
      static const unsigned int PairLJ612CutDistanceSQ
        = PairLJ612PostName::PairLJ612NumberPost;
      static const unsigned int PairLJ612CutDistance      = 3;
      static const unsigned int PairLJ612CutIvDistance    = 4;
      static const unsigned int PairLJ612CutNumberPost    = 5;

  };

  const unsigned int PairLJ612CutPostName::PairLJ612CutIvDistanceSQ;
  const unsigned int PairLJ612CutPostName::PairLJ612CutIvDistance6;
  const unsigned int PairLJ612CutPostName::PairLJ612CutDistanceSQ;
  const unsigned int PairLJ612CutPostName::PairLJ612CutDistance;
  const unsigned int PairLJ612CutPostName::PairLJ612CutIvDistance;
  const unsigned int PairLJ612CutPostName::PairLJ612CutNumberPost;

}

#endif

