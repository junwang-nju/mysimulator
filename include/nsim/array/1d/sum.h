
#ifndef _Array_1D_Sum_H_
#define _Array_1D_Sum_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  T Sum(const Array1D<T>& V) {
    T sum=0;
    for(unsigned int i=0;i<V.Size();++i)  sum+=V[i];
    return sum;
  }

}

#endif

