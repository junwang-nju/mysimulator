
#ifndef _Interaction_Func_Pairwise_CoreLJ612_Post_Name_H_
#define _Interaction_Func_Pairwise_CoreLJ612_Post_Name_H_

#include "interaction-func/pairwise/lj612/post-name.h"

namespace mysimulator {

  enum CoreLJ612PostName {
    CoreLJ612IvDistanceSQ = LJ612IvDistanceSQ,
    CoreLJ612IvDistance6  = LJ612IvDistance6,
    CoreLJ612DistanceSQ   = LJ612NumberPost,
    CoreLJ612NumberPost
  };

}

#endif

