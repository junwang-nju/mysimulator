
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Diff_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Diff_H_

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/dist-coulomb/buffer/post-name.h"
#include "intrinsic-type/square.h"

namespace mysimulator {

  template <typename T>
  void DiffDistCoulomb(const T* post,const Unique64Bit* P,T* diff) {
    *diff=P[DistCoulombDualStrength].value<T>()
         *square(post[DistCoulombIvDistanceSQ]);
  }

}

#endif

