
#ifndef _Vector_Sum_H_
#define _Vector_Sum_H_

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  T sum(const Vector<T>& v) {
    assert(IsValid(v));
    T s;
    copy(s,static_cast<T>(cZero));
    T* p=const_cast<T*>(v());
    T* pend=p+v.size;
    for(;p!=pend;)  shift(p,cOne,*(p++));
    return s;
  }

  double sum(const Vector<double>& v) {
    assert(IsValid(v));
    return ddot_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
                 const_cast<double*>(v()),const_cast<long*>(&lOne),
                 const_cast<double*>(&dOne),const_cast<long*>(&lZero));
  }

  float sum(const Vector<float>& v) {
    assert(IsValid(v));
    return sdot_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
                 const_cast<float*>(v()),const_cast<long*>(&lOne),
                 const_cast<float*>(&fOne),const_cast<long*>(&lZero));
  }

  template <typename T>
  T asum(const Vector<T>& v) {
    assert(IsValid(v));
    T s;
    copy(s,static_cast<T>(cZero));
    T* p=const_cast<T*>(v());
    T* pend=p+v.size;
    for(;p!=pend;)  shift(p,cOne,absval(*(p++)));
    return s;
  }

  double asum(const Vector<double>& v) {
    assert(IsValid(v));
    return dasum_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
                  const_cast<double*>(v()),const_cast<long*>(&lOne));
  }

  float asum(const Vector<float>& v) {
    assert(IsValid(v));
    return sasum_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
                  const_cast<float*>(v()),const_cast<long*>(&lOne));
  }

}

#endif

