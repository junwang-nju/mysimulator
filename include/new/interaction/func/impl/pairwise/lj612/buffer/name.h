
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Buffer_Name_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Buffer_Name_H_

#include "interaction/func/impl/pairwise/common/buffer/name.h"

namespace mysimulator {

  enum LJ612BufferName {
    LJ612IvDistanceSQ=PairwiseCommonBufferSize,
    LJ612IvDistance6,
    LJ612BufferSize
  };

}

#endif

