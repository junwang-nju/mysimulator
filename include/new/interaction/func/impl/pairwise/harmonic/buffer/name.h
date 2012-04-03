
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_Name_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_Name_H_

#include "interaction/func/impl/pairwise/common/buffer/name.h"

namespace mysimulator {

  enum HarmonicBufferName {
    HarmonicLength=PairwiseCommonBufferSize,
    HarmonicIvLength,
    HarmonicBufferSize
  };

}

#endif

