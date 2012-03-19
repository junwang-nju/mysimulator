
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_Name_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_Name_H_

#include "interaction/func/impl/pairwise/common/buffer/name.h"

namespace mysimulator {

  enum CoulombBufferName {
    CoulombIvDistanceSQ = PairwiseCommonBufferSize,
    CoulombIvDistance,
    CoulombBufferSize
  };

}

#endif

