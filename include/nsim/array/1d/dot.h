
#ifndef _Array_1D_Dot_H_
#define _Array_1D_Dot_H_

#include "array/1d/interface.h"
#include "intrinsic-type/reflection/dual.h"

#ifndef _DotType
#define _DotType(T1,T2) typename _Dual<T1,T2>::CombineType
#else
#error "Duplicate Definition for Macro _DotType"
#endif

namespace mysimulator {

  template <typename T1,typename T2>
  _DotType(T1,T2) Dot(const Array1D<T1>& V1,const Array1D<T2>& V2) {
    assert((n<=V1.Size())&&(n<=V2.Size()));
    _DotType(T1,T2) sum=0.;
    for(unsigned int i=0;i<n;++i) sum+=V1[i]*V2[i];
    return sum;
  }

}

#ifdef _DotType
#undef _DotType
#endif

#include "linear-algebra/blas.h"

namespace mysimulator {

  double BlasDot(const Array1D<double>& V1,const Array1D<double>& V2,
                 unsigned int n) {
    assert((n<=V1.Size())&&(n<=V2.Size()));
    long m=n, one=1;
    return BLAS<double>::Dot(&m,const_cast<double*>(V1._data),&one,
                                const_cast<double*>(V2._data),&one);
  }

  float BlasDot(const Array1D<float>& V1,const Array1D<float>& V2,
                 unsigned int n) {
    assert((n<=V1.Size())&&(n<=V2.Size()));
    long m=n, one=1;
    return BLAS<float>::Dot(&m,const_cast<float*>(V1._data),&one,
                               const_cast<float*>(V2._data),&one);
  }

}

#endif

