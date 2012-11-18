
#ifndef _Array_2D_Interface_H_
#define _Array_2D_Interface_H_

#include "array/def.h"

#include "array-2d/general.h"
#include "array-2d/general-value.h"
#include "array-2d/intrinsic.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DK1,ArrayKernelName LK1,
                       ArrayKernelName DK2,ArrayKernelName LK2>
  void __imprint(Array2D<T,DK1,LK1>& A, const Array2D<T,DK2,LK2>& B) {
    A.imprint(B);
  }

}

namespace std {

  template <typename T,mysimulator::ArrayKernelName DK,
                       mysimulator::ArrayKernelName LK,bool vF>
  void swap(mysimulator::Array2D<T,DK,LK,vF>& A,
            mysimulator::Array2D<T,DK,LK,vF>& B) {
    A.swap(B);
  }

}

#endif

