
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_PostName_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_PostName_H_

#include "interaction/func/impl/pairwise/common/buffer/post-name.h"

namespace mysimulator {

  enum HarmonicBufferPostName {
    HarmonicLength=PairwiseCommonBufferPostSize,
    HarmonicIvLength,
    HarmonicBufferPostSize
  };

}

#endif

