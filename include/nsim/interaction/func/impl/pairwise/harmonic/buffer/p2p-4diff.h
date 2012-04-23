
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_P2P4Diff_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_P2P4Diff_H_

#include "intrinsic-type/square-root.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/post-name.h"
#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void HarmonicPre2Post4Diff(
      const Array1D<T>& pre,const Array1D<Unique64Bit>&,Array1D<T>& post,
      bool& flag) {
    post[HarmonicIvLength]=1./sqroot(pre[PairwiseDistanceSQ]);
    flag=true;
  }

}

#endif
