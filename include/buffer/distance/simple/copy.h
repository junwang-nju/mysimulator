
#ifndef _Buffer_Distance_Simple_Copy_H_
#define _Buffer_Distance_Simple_Copy_H_

#include "buffer/distance/simple/interface.h"
#include "buffer/distance/base/copy.h"

namespace mysimulator {

  template <typename T, typename cT>
  void copy(SimpleDistanceBuffer<T>& B, const SimpleDistanceBuffer<cT>& cB) {
    copy(static_cast<DistanceBufferBase<T>&>(B),
         static_cast<DistanceBufferBase<cT>&>(cB));
  }

}

#endif

