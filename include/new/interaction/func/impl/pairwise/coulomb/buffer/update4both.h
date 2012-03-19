
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_Update4Both_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_Update4Both_H_

#include "interaction/func/impl/pairwise/coulomb/buffer/update4diff.h"

namespace mysimulator {

  template <typename T>
  void CoulombUpdate4Both(const T& dsq, const Unique64Bit* P,T* buffer) {
    CoulombUpdate4Diff(dsq,P,buffer);
  }

}

#endif

