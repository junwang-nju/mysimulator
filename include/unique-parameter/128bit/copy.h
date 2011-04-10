
#ifndef _Unique_Parameter_128bit_Copy_H_
#define _Unique_Parameter_128bit_Copy_H_

#include "unique-parameter/128bit/interface.h"
#include "linear-algebra/blas.h"

namespace mysimulator {

  void copy(UniqueParameter128Bit& P, const UniqueParameter128Bit& cP) {
#ifdef _Have_SSE2
    P.si=_mm_loadu_si128(&(cP.si));
#else
    P.ull[0]=cP.ull[0];   P.ull[1]=cP.ull[1];
#endif
  }

  template <typename T>
  void copy(UniqueParameter128Bit& P, const T& value) {
    copy(P.value<T>(),value);
  }

  template <typename T>
  void copy(UniqueParameter128Bit& P, T* const& ptr) { copy(P.pvalue,ptr); }

  template <typename T>
  void copy(T& value, const UniqueParameter128Bit& P) {
    copy(value,P.value<T>());
  }

  template <typename T>
  void copy(T*& ptr, const UniqueParameter128Bit& P) { copy(ptr,P.pvalue); }

}

#include "vector/interface.h"

namespace mysimulator {
  
  void copy(Vector<UniqueParameter128Bit>& v,
            const Vector<UniqueParameter128Bit>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    n+=n;
    dcopy_(&n,
        reinterpret_cast<double*>(const_cast<UniqueParameter128Bit*>(cv())),
        const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
        const_cast<long*>(&lOne));
  }
  
  void copy(Vector<UniqueParameter128Bit>& v, const Vector<long double>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    n+=n;
    dcopy_(&n,
        reinterpret_cast<double*>(const_cast<long double*>(cv())),
        const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
        const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter128Bit>& v, const Vector<double>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,const_cast<double*>(cv()),const_cast<long*>(&lOne),
           reinterpret_cast<double*>(v()),const_cast<long*>(&lTwo));
  }

  void copy(Vector<UniqueParameter128Bit>& v,
            const Vector<unsigned long long>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,reinterpret_cast<double*>(const_cast<unsigned long long*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lTwo));
  }

  void copy(Vector<UniqueParameter128Bit>& v, const Vector<float>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,const_cast<float*>(cv()),const_cast<long*>(&lOne),
           reinterpret_cast<float*>(v()),const_cast<long*>(&lFour));
  }

  void copy(Vector<UniqueParameter128Bit>& v, const Vector<int>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<int*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lFour));
  }

  void copy(Vector<UniqueParameter128Bit>& v, const Vector<unsigned int>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<unsigned int*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lFour));
  }

}

#endif
