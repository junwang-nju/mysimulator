
#ifndef _Vector_Swap_H_
#define _Vector_Swap_H_

#include "vector/interface.h"
#include "vector/exchange.h"

namespace mysimulator {

  template <typename T>
  void swap(Vector<T>& va, Vector<T>& vb) {
    exchange(va(),vb());
    exchange(va.size,vb.size);
    exchange(va.state,vb.state);
  }

}

#endif

