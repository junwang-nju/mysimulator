
#ifndef _Array_1D_Content_SquareRoot_H_
#define _Array_1D_Content_SquareRoot_H_

#include "array/1d/content/interface.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void sqroot(Array1DContent<T>& A) {
    for(unsigned int i=0;i<A.size;++i)  copy(A[i],sqroot(A[i]));
  }

}

#endif

