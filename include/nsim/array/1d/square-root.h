
#ifndef _Array_1D_SquareRoot_H_
#define _Array_1D_SquareRoot_H_

#include "array/1d/interface.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void Sqroot(Array1D<T>& V) {
    for(unsigned int i=0;i<V.Size();++i)  V[i]=Sqroot(V[i]);
  }

}

#endif

