
#ifndef _Interaction_Func_Pairwise_LJ1012Cut_Post_Name_H_
#define _Interaction_Func_Pairwise_LJ1012Cut_Post_Name_H_

#include "interaction-func/pairwise/lj1012/post-name.h"

namespace mysimulator {

  enum LJ1012CutPostName {
    LJ1012CutIvDistanceSQ   = LJ1012IvDistanceSQ,
    LJ1012CutIvDistance10   = LJ1012IvDistance10,
    LJ1012CutDistanceSQ     = LJ1012NumberPost,
    LJ1012CutDistance,
    LJ1012CutIvDistance,
    LJ1012CutNumberPost
  };

}

#endif

