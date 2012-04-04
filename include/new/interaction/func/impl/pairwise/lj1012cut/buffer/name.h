
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_Name_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_Name_H_

#include "interaction/func/impl/pairwise/lj1012/buffer/name.h"

namespace mysimulator {

  enum LJ1012CutBufferName {
    LJ1012CutIvDistanceSQ   = LJ1012IvDistanceSQ,
    LJ1012CutIvDistance10   = LJ1012IvDistance10,
    LJ1012CutDistanceSQ     = LJ1012BufferSize,
    LJ1012CutDistance,
    LJ1012CutIvDistance,
    LJ1012CutBufferSize
  };

}

#endif

