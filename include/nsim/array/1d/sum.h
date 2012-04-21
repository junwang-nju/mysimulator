
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

#include "intrinsic-type/abs-value.h"

namespace mysimulator {

  template <typename T>
  T AbsSum(const Array1D<T>& V) {
    T sum=0;
    for(unsigned int i=0;i<V.Size();++i)  sum+=absval(V[i]);
    return sum;
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  double BlasAbsSum(const Array1D<double>& V) {
    long m=V.Size(), one=1;
    return BLAS<double>::ASum(&m,const_cast<double*>(V._data),&one);
  }

  float BlasAbsSum(const Array1D<float>& V) {
    long m=V.Size(), one=1;
    return BLAS<float>::ASum(&m,const_cast<float*>(V._data),&one);
  }

}

#endif

