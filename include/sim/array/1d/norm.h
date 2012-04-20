
#ifndef _Array_1D_Norm_H_
#define _Array_1D_Norm_H_

#include "array/1d/dot.h"

namespace mysimulator {

  template <typename T>
  T normSQ(const T* p) { return dot(p,p); }

}

#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  T norm(const T* p) { return sqroot(normSQ(p)); }

  double norm(const double* p) {
    long n=size(p), one=1;
    return BLAS<double>::Norm(&n,const_cast<double*>(p),&one);
  }

  float norm(const float* p) {
    long n=size(p), one=1;
    return BLAS<float>::Norm(&n,const_cast<float*>(p),&one);
  }

}

#endif

