
#ifndef _Array_1D_Norm_H_
#define _Array_1D_Norm_H_

#include "array/1d/dot.h"

namespace mysimulator {

  template <typename T>
  T NormSQ(const Array1D<T>& V,unsigned int n) { return Dot(V,V,n); }

  template <typename T>
  T BlasNormSQ(const Array1D<T>& V,unsigned int n) { return BlasDot(V,V,n); }

}

#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  T Norm(const Array1D<T>& V,unsigned int n) { return sqroot(NormSQ(V,n)); }

  double BlasNorm(const Array1D<double>& V,unsigned int n) {
    long m=n, one=1;
    return BLAS<double>::Norm(&m,const_cast<double*>(V._data),&one);
  }

  float BlasNorm(const Array1D<float>& V,unsigned int n) {
    long m=n, one=1;
    return BLAS<float>::Norm(&m,const_cast<float*>(V._data),&one);
  }

}

#endif

