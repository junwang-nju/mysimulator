
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Buffer_PostName_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Buffer_PostName_H_

#include "interaction/func/impl/pairwise/lj612/buffer/post-name.h"

namespace mysimulator {

  enum LJ612CutBufferPostName {
    LJ612CutIvDistanceSQ = LJ612IvDistanceSQ,
    LJ612CutIvDistance6  = LJ612IvDistance6,
    LJ612CutDistanceSQ   = LJ612BufferPostSize,
    LJ612CutDistance,
    LJ612CutIvDistance,
    LJ612CutBufferPostSize
  };

}

#endif

