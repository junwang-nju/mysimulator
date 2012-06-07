
#ifndef _Interaction_Func_Pairwise_LJ612Cut_Post_Name_H_
#define _Interaction_Func_Pairwise_LJ612Cut_Post_Name_H_

#include "interaction-func/pairwise/lj612/post-name.h"

namespace mysimulator {

  enum LJ612CutPostName {
    LJ612CutIvDistanceSQ  = LJ612IvDistanceSQ,
    LJ612CutIvDistance6   = LJ612IvDistance6,
    LJ612CutDistanceSQ    = LJ612NumberPost,
    LJ612CutDistance,
    LJ612CutIvDistance,
    LJ612CutNumberPost
  };

}

#endif

