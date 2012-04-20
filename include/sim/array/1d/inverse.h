
#ifndef _Array_1D_Inverse_H_
#define _Array_1D_Inverse_H_

#include "array/1d/size.h"
#include "intrinsic-type/inverse.h"

namespace mysimulator {

  template <typename T>
  void Inverse(T* p) {
    assert(p!=NULL);
    unsigned int n=size(p);
    for(unsigned int i=0;i<n;++i) inverse(p[i]);
  }

}

#endif

