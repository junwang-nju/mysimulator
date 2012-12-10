
#ifndef _System_Interaction_Function_Pairwise_CoreLJ612_Post_Name_H_
#define _System_Interaction_Function_Pairwise_CoreLJ612_Post_Name_H_

#include "system/interaction/function/pairwise/lj612/post-name.h"

namespace mysimulator {

  class PairCoreLJ612PostName : public PairLJ612PostName {

    public:

      typedef PairLJ612PostName ParentType;

      static const unsigned int DistanceSQ      = ParentType::NumberPost;
      static const unsigned int NumberPost      = DistanceSQ+1;

  };

  const unsigned int PairCoreLJ612PostName::DistanceSQ;
  const unsigned int PairCoreLJ612PostName::NumberPost;

}

#endif

