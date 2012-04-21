
#ifndef _Array_1D_Inverse_H_
#define _Array_1D_Inverse_H_

#include "array/1d/interface.h"
#include "intrinsic-type/inverse.h"

namespace mysimulator {

  template <typename T>
  void Inverse(Array1D<T>& V,unsigned int n) {
    assert(n<=V.Size());
    for(unsigned int i=0;i<n;++i) Inverse(V[i]);
  }

}

#endif

