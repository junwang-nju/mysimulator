
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Buffer_Name_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Buffer_Name_H_

#include "interaction/func/impl/pairwise/lj612/buffer/name.h"

namespace mysimulator {

  enum LJ612CutBufferName {
    LJ612CutIvDistanceSQ = LJ612IvDistanceSQ,
    LJ612CutIvDistance6  = LJ612IvDistance6,
    LJ612CutDistanceSQ   = LJ612BufferSize,
    LJ612CutDistance,
    LJ612CutIvDistance,
    LJ612CutBufferSize
  };

}

#endif

