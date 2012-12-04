
#ifndef _System_Interaction_Function_Pairwise_LJ612Cut_Post_Name_H_
#define _System_Interaction_Function_Pairwise_LJ612Cut_Post_Name_H_

#include "system/interaction/function/pairwise/lj612/post-name.h"

namespace mysimulator {

  class PairLJ612CutPostName : public PairLJ612PostName {

    public:

      typedef PairLJ612PostName ParentType;

      static const unsigned int DistanceSQ = ParentType::NumberPost;
      static const unsigned int Distance   = DistanceSQ+1;
      static const unsigned int IvDistance = Distance+1;
      static const unsigned int NumberPost = IvDistance+1;

  };

  const unsigned int PairLJ612CutPostName::DistanceSQ;
  const unsigned int PairLJ612CutPostName::Distance;
  const unsigned int PairLJ612CutPostName::IvDistance;
  const unsigned int PairLJ612CutPostName::NumberPost;

}

#endif

