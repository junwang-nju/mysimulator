
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Diff_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Diff_H_

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/dist-coulomb/buffer/post-name.h"
#include "intrinsic-type/square.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void DiffDistCoulomb(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* diff) {
    *diff=Value<T>(P[DistCoulombDualStrength])
         *Square(post[DistCoulombIvDistanceSQ]);
  }

}

#endif

