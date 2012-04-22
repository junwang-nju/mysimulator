
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Buffer_P2P4Both_H_

#include "interaction/func/impl/pairwise/corelj612/buffer/p2p-4diff.h"

namespace mysimulator {

  template <typename T>
  void CoreLJ612Pre2Post4Both(
      const Array1D<T>& pre,const Array1D<Unique64Bit>& P,Array1D<T>& post,
      bool& flag) {
    CoreLJ612Pre2Post4Diff(pre,P,post,flag);
  }

}

#endif

