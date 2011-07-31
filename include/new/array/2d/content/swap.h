
#ifndef _Array_2D_Content_Swap_H_
#define _Array_2D_Content_Swap_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/swap.h"

namespace mysimulator {

  template <typename T>
  void Swap(Array2DContent<T>& A1, Array2DContent<T>& A2) {
    Swap(A1.base,A2.base);
    Swap(A1.infra,A2.infra);
  }

}

#endif

