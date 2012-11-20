
#ifndef _Array_2D_Kernel_Sum_H_
#define _Array_2D_Kernel_Sum_H_

#include "array-2d/def.h"
#include "array/interface.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DK,ArrayKernelName LK>
  T __sum_2d(Array2D<Intrinsic<T>,DK,LK> const& A) { return A.Data().Sum(); }

  template <typename T,ArrayKernelName DK>
  T __sum_2d(Array2D<Intrinsic<T>,DK,ArrayKernelName::SSE> const& A) {
    return ((Array<Array<Intrinsic<T>,ArrayKernelName::SSE>> const&)A).Sum();
  }

}

#endif

