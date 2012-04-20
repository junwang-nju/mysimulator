
#ifndef _Array_1D_Sum_H_
#define _Array_1D_Sum_H_

#include "array/1d/size.h"

namespace mysimulator {

  template <typename T>
  T Sum(const T* p) {
    T sum=0;
    T *r=const_cast<T*>(p);
    T *rend=r+size(p);
    for(;r!=rend;)  sum+=*(r++);
    return sum;
  }

}

#include "intrinsic-type/abs-value.h"

namespace mysimulator {

  template <typename T>
  void AbsSum(const T* p) {
    T sum=0;
    T *r=const_cast<T*>(p);
    T *rend=r+size(p);
    for(;r!=rend;)  sum+=absval(*(r++));
    return sum;
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  double AbsSum(const double* p) {
    long n=size(p),one=1;
    return BLAS<double>::ASum(&n,const_cast<double*>(p),&one);
  }

  float AbsSum(const float* p) {
    long n=size(p),one=1;
    return BLAS<float>::ASum(&n,const_cast<float*>(p),&one);
  }

}

#endif

