
#ifndef _Array_1D_Content_Swap_H_
#define _Array_1D_Content_Swap_H_

#include "array/1d/content/interface.h"
#include "intrinsic-type/exchange.h"

namespace mysimulator {

  template <typename T>
  void Swap(Array1DContent<T>& A1, Array1DContent<T>& A2) {
    exchange(A1.size,A2.size);
    exchange(A1.first,A2.first);
    exchange(A1.last,A2.last);
    exchange(A1.head,A2.head);
    exchange(A1.start,A2.start);
  }

}

#endif

