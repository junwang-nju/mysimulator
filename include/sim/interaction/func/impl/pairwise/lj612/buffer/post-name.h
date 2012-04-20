
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Buffer_PostName_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Buffer_PostName_H_

#include "interaction/func/impl/pairwise/common/buffer/post-name.h"

namespace mysimulator {

  enum LJ612BufferPostName {
    LJ612IvDistanceSQ=PairwiseCommonBufferPostSize,
    LJ612IvDistance6,
    LJ612BufferPostSize
  };

}

#endif

