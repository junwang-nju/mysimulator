
#ifndef _Array_1D_Norm_H_
#define _Array_1D_Norm_H_

#include "array/1d/dot.h"

namespace mysimulator {

  template <typename T>
  T NormSQ(const T* p, unsigned int n) { return Dot(p,p,n); }

  template <typename T>
  T BLASNormSQ(const T* p, unsigned int n) { return BLASDot(p,n); }

}

#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  T Norm(const T* p,unsigned int n) { return sqroot(NormSQ(p,n)); }

  double BLASNorm(const double* p,unsigned int n) {
    long m=n, one=1;
    return BLAS<double>::Norm(&m,const_cast<double*>(p),&one);
  }

  float BLASNorm(const float* p, unsigned int n) {
    long m=n, one=1;
    return BLAS<float>::Norm(&m,const_cast<float*>(p),&one);
  }

}

#endif

