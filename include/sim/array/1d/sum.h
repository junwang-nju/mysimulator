
#ifndef _Array_1D_Sum_H_
#define _Array_1D_Sum_H_

namespace mysimulator {

  template <typename T>
  T Sum(const T* p, unsigned int n) {
    T sum=0;
    T *r=const_cast<T*>(p);
    T *rend=r+n;
    for(;r!=rend;)  sum+=*(r++);
    return sum;
  }

}

#include "intrinsic-type/abs-value.h"

namespace mysimulator {

  template <typename T>
  void AbsSum(const T* p, unsigned int n) {
    T sum=0;
    T *r=const_cast<T*>(p);
    T *rend=r+n;
    for(;r!=rend;)  sum+=absval(*(r++));
    return sum;
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  double BLASAbsSum(const double* p, unsigned int n) {
    long m=n,one=1;
    return BLAS<double>::ASum(&m,const_cast<double*>(p),&one);
  }

  float BLASAbsSum(const float* p, unsigned int n) {
    long m=n,one=1;
    return BLAS<float>::ASum(&m,const_cast<float*>(p),&one);
  }

}

#endif

