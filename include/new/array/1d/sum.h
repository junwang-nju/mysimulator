
#ifndef _Array_1D_Sum_H_
#define _Array_1D_Sum_H_

#include "array/1d/interface.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename T>
  T sum(const Array1D<T>& v) {
    assert(IsValid(v));
    T s;
    copy(s,static_cast<T>(cZero));
    T* p=const_cast<T*>(v.start);
    T* e=p+v.size;
    for(;p!=e;) shift(s,*(p++));
    return s;
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  template <typename T>
  T _sum(const Array1D<T>& v) {
    assert(IsValid(v));
    return BLAS<T>::Dot(
        reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
        const_cast<T*>(v.start),const_cast<long*>(&lOne),
        const_cast<T*>(&ValueOne<T>()),const_cast<long*>(&lZero));
  }

  double sum(const Array1D<double>& v) { return _sum(v); }

  float sum(const Array1D<float>& v) { return _sum(v); }

}

#include "intrinsic-type/abs-value.h"

namespace mysimulator {

  template <typename T>
  T asum(const Array1D<T>& v) {
    assert(IsValid(v));
    T s;
    copy(s,static_cast<T>(cZero));
    T* p=const_cast<T*>(v.start);
    T* e=p+v.size;
    for(;p!=e;) shift(s,absval(*(p++)));
    return s;
  }

  template <typename T>
  T _asum(const Array1D<T>& v) {
    assert(IsValid(v));
    return BLAS<T>::ASum(
        reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
        const_cast<T*>(v.start),const_cast<long*>(&lOne));
  }

  double asum(const Array1D<double>& v) { return _asum(v); }

  float asum(const Array1D<float>& v) { return _asum(v); }

}

#endif

