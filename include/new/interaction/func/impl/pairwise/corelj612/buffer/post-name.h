
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Buffer_PostName_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Buffer_PostName_H_

#include "interaction/func/impl/pairwise/lj612/buffer/post-name.h"

namespace mysimulator {

  enum CoreLJ612BufferPostName {
    CoreLJ612IvDistanceSQ = LJ612IvDistanceSQ,
    CoreLJ612IvDistance6  = LJ612IvDistance6,
    CoreLJ612DistanceSQ   = LJ612BufferPostSize,
    CoreLJ612BufferPostSize
  };

}

#endif

