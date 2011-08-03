
#ifndef _Map_Allocate_H_
#define _Map_Allocate_H_

#include "map/interface.h"
#include "chain/allocate.h"

namespace mysimulator {

  template <typename KT, typename VT>
  void allocate(Map<KT,VT>& M) { release(M); allocate(M.data); }

}

#endif

