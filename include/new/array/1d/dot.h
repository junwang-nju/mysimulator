
#ifndef _Array_1D_Dot_H_
#define _Array_1D_Dot_H_

#include "array/1d/interface.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/shift.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T1, typename T2>
  typename _Dual<T1,T2>::CombineType
  dot(const Array1D<T1>& va, const Array1D<T2>& vb) {
    typedef typename _Dual<T1,T2>::CombineType  Type;
    assert(IsValid(va)&&IsValid(vb));
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    Type sum;
    copy(sum,static_cast<Type>(cZero));
    T1* ap=const_cast<T1*>(va.start);
    T2* bp=const_cast<T2*>(vb.start);
    T1* ae=ap+n;
    for(;ap!=ae;) shift(sum,*(ap++),*(bp++));
    return sum;
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  double dot(const Array1D<double>& va, const Array1D<double>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    return BLAS<double>::Dot(
        &n,const_cast<double*>(va.start),const_cast<long*>(&lOne),
           const_cast<double*>(vb.start),const_cast<long*>(&lOne));
  }

  float dot(const Array1D<float>& va, const Array1D<float>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    return BLAS<float>::Dot(
        &n,const_cast<float*>(va.start),const_cast<long*>(&lOne),
           const_cast<float*>(vb.start),const_cast<long*>(&lOne));
  }

}

#endif


