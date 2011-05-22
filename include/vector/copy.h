
#ifndef _Vector_Copy_H_
#define _Vector_Copy_H_

#include "vector/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {
  
  template <typename T, typename cT>
  void copy(Vector<T>& v, const Vector<cT>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    unsigned int n=(v.size<cv.size?v.size:cv.size);
    T* p=v.pdata;
    cT* cp=const_cast<cT*>(cv.pdata);
    T* pend=p+n;
    for(;p!=pend;) copy(*(p++),*(cp++));
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void copy(Vector<double>& v, const Vector<double>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,const_cast<double*>(cv()),const_cast<long*>(&lOne),
           v(),const_cast<long*>(&lOne));
  }

  void copy(Vector<float>& v, const Vector<float>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,const_cast<float*>(cv()),const_cast<long*>(&lOne),
           v(),const_cast<long*>(&lOne));
  }

  void copy(Vector<long long>& v, const Vector<long long>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,reinterpret_cast<double*>(const_cast<long long*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<unsigned long long>& v,
            const Vector<unsigned long long>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,reinterpret_cast<double*>(const_cast<unsigned long long*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& v, const Vector<int>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<int*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<unsigned int>& v, const Vector<unsigned int>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<unsigned int*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

}

#include <cstring>

namespace mysimulator {

  void copy(Vector<short>& v, const Vector<short>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n+n);
  }
  
  void copy(Vector<unsigned short>& v, const Vector<unsigned short>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n+n);
  }

  void copy(Vector<char>& v, const Vector<char>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n);
  }

  void copy(Vector<char>& v, const Vector<unsigned char>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n);
  }

  void copy(Vector<unsigned char>& v, const Vector<unsigned char>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n);
  }

  void copy(Vector<unsigned char>& v, const Vector<char>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n);
  }

}

#endif
