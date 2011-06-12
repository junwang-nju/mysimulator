
#ifndef _Buffer_Distance_Base_Copy_H_
#define _Buffer_Distance_Base_Copy_H_

#include "buffer/distance/base/interface.h"
#include "unique-parameter/64bit/copy.h"
#include "vector/copy.h"

namespace mysimulator {

  template <typename T, typename cT>
  void copy(DistanceBufferBase<T>& B, const DistanceBufferBase<cT>& cB) {
    assert(IsValid(B)&&IsValid(cB));
    copy(B.data,cB.data);
    copy(B.DisplaceVector,cB.DisplaceVector);
  }

}

#endif

