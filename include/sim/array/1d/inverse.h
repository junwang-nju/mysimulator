
#ifndef _Array_1D_Inverse_H_
#define _Array_1D_Inverse_H_

#include "intrinsic-type/inverse.h"

namespace mysimulator {

  template <typename T>
  void Inverse(T* p, unsigned int n) {
    for(unsigned int i=0;i<n;++i) inverse(p[i]);
  }

}

#endif

