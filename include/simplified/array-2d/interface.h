
#ifndef _Array_2D_Interface_H_
#define _Array_2D_Interface_H_

#include "array/def.h"

#include "array-2d/general.h"
#include "array-2d/general-value.h"

namespace std {

  template <typename T,mysimulator::ArrayKernelName DK,
                       mysimulator::ArrayKernelName LK,bool vF>
  void swap(mysimulator::Array2D<T,DK,LK,vF>& A,
            mysimulator::Array2D<T,DK,LK,vF>& B) {
    A.swap(B);
  }

}

#endif

