
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_PostName_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_PostName_H_

#include "interaction/func/impl/pairwise/common/buffer/post-name.h"

namespace mysimulator {

  enum CoulombBufferPostName {
    CoulombIvDistanceSQ = PairwiseCommonBufferPostSize,
    CoulombIvDistance,
    CoulombBufferPostSize
  };

}

#endif

