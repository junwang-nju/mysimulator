
#ifndef _Array_1D_Dot_H_
#define _Array_1D_Dot_H_

#include "array/1d/size.h"
#include "intrinsic-type/reflection/dual.h"

#ifndef _DotType
#define _DotType(T1,T2) typename _Dual<T1,T2>::CombineType
#else
#error "Duplication Definition for _DotType"
#endif

namespace mysimulator {

  template <typename T1,typename T2>
  _DotType(T1,T2) Dot(const T1* p, const T1* q) {
    unsigned int n=size(p);
    assert(n==size(q));
    _DotType(T1,T2) sum=0;
    for(unsigned int i=0;i<n;++i) sum+=p[i]*q[i];
    return sum;
  }

}

#ifdef _DotType
#undef _DotType
#endif

#include "linear-algebra/blas.h"

namespace mysimulator {

  double Dot(const double* p, const double* q) {
    long n=size(p),one=1;
    assert(static_cast<unsigned int>(n)==size(q));
    return BLAS<double>::Dot(&n,const_cast<double*>(p),&one,
                                const_cast<double*>(q),&one);
  }

  float Dot(const float* p, const float* q) {
    long n=size(p),one=1;
    assert(static_cast<unsigned int>(n)==size(q));
    return BLAS<float>::Dot(&n,const_cast<float*>(p),&one,
                               const_cast<float*>(q),&one);
  }

}

#endif

