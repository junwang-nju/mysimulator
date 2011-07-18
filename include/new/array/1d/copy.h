
#ifndef _Array_1D_Copy_H_
#define _Array_1D_Copy_H_

#include "array/1d/interface.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void copy(Array1D<T1>& v, const Array1D<T2>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    unsigned int n=(v.size<cv.size?v.size:cv.size);
    T1* p=v.start;
    T2* q=const_cast<T2*>(cv.start);
    T1* e=p+n;
    for(;p!=e;) copy(*(p++),*(q++));
  }

}

#include "linear-algebra/blas.h"
#include "array/reflection/single.h"

namespace mysimulator {

  template <typename T>
  void copy(Array1D<T>& v, const Array1D<T>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    typedef typename _Single_Array<T>::OperateType Type;
    long n=(v.size<cv.size?v.size:cv.size);
    BLAS<Type>::Copy(
        &n,reinterpret_cast<Type*>(const_cast<T*>(cv.start)),
        const_cast<long*>(&lOne),reinterpret_cast<Type*>(v.start),
        const_cast<long*>(&lOne));
  }

  void copy(Array1D<long double>& v, const Array1D<long double>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    n=n+n+n;
    scopy_(
        &n,reinterpret_cast<float*>(const_cast<long double*>(cv.start)),
        const_cast<long*>(&lOne),reinterpret_cast<float*>(v.start),
        const_cast<long*>(&lOne));
  }

}

#include <cstring>

namespace mysimulator {

  template <typename T>
  void _copy(Array1D<T>& v, const Array1D<T>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v.start,cv.start,n*sizeof(T));
  }

  void copy(Array1D<short>& v, const Array1D<short>& cv) { _copy(v,cv); }

  void copy(Array1D<unsigned short>& v, const Array1D<unsigned short>& cv) {
    _copy(v,cv);
  }

  void copy(Array1D<char>& v, const Array1D<char>& cv) { _copy(v,cv); }

  void copy(Array1D<unsigned char>& v, const Array1D<unsigned char>& cv) {
    _copy(v,cv);
  }

  void copy(Array1D<char>& v, const Array1D<unsigned char>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v.start,cv.start,n);
  }

  void copy(Array1D<unsigned char>& v, const Array1D<char>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v.start,cv.start,n);
  }

}

#endif

