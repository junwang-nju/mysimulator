
#ifndef _Array_1D_Dot_H_
#define _Array_1D_Dot_H_

#include "intrinsic-type/reflection/dual.h"

#ifndef _DotType
#define _DotType(T1,T2) typename _Dual<T1,T2>::CombineType
#else
#error "Duplication Definition for _DotType"
#endif

namespace mysimulator {

  template <typename T1,typename T2>
  _DotType(T1,T2) Dot(const T1* p, const T1* q, unsigned int n) {
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

  double BLASDot(const double* p, const double* q, unsigned int n) {
    long m=n,one=1;
    return BLAS<double>::Dot(&m,const_cast<double*>(p),&one,
                                const_cast<double*>(q),&one);
  }

  float BLASDot(const float* p, const float* q, unsigned int n) {
    long m=n,one=1;
    return BLAS<float>::Dot(&m,const_cast<float*>(p),&one,
                               const_cast<float*>(q),&one);
  }

}

#endif

