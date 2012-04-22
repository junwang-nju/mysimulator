
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_PostName_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_PostName_H_

#include "interaction/func/impl/pairwise/lj1012/buffer/post-name.h"

namespace mysimulator {

  enum LJ1012CutBufferPostName {
    LJ1012CutIvDistanceSQ   = LJ1012IvDistanceSQ,
    LJ1012CutIvDistance10   = LJ1012IvDistance10,
    LJ1012CutDistanceSQ     = LJ1012BufferPostSize,
    LJ1012CutDistance,
    LJ1012CutIvDistance,
    LJ1012CutBufferPostSize
  };

}

#endif

