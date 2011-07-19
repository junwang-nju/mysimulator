
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

  template <typename T>
  T _dot(const Array1D<T>& va, const Array1D<T>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    return BLAS<T>::Dot(&n,const_cast<T*>(va.start),const_cast<long*>(&lOne),
                           const_cast<T*>(vb.start),const_cast<long*>(&lOne));
  }

  double dot(const Array1D<double>& va, const Array1D<double>& vb) {
    return _dot(va,vb);
  }

  float dot(const Array1D<float>& va, const Array1D<float>& vb) {
    return _dot(va,vb);
  }

}

#endif


