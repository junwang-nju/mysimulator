
#ifndef _Unique_Parameter_64bit_Copy_H_
#define _Unique_Parameter_64bit_Copy_H_

#include "unique-parameter/64bit/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {
  
  void copy(UniqueParameter64Bit& P, const UniqueParameter64Bit& cP) {
    P.ull=cP.ull;
  }

  template <typename T>
  void copy(UniqueParameter64Bit& P, const T& value) {
    copy(P.value<T>(),value);
  }

  template <typename T>
  void copy(UniqueParameter64Bit& P, T* const& ptr) { copy(P.ptr[0],ptr); }

  template <typename T>
  void copy(T& value, const UniqueParameter64Bit& P) {
    copy(value,P.value<T>());
  }

  template <typename T>
  void copy(T*& ptr, const UniqueParameter64Bit& P) { copy(ptr,P.ptr[0]); }
  
}

#include "vector/interface.h"
#include "linear-algebra/blas.h"

namespace mysimulator {

  void copy(Vector<UniqueParameter64Bit>& v,
            const Vector<UniqueParameter64Bit>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,
           reinterpret_cast<double*>(const_cast<UniqueParameter64Bit*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter64Bit>& v, const Vector<double>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,const_cast<double*>(cv()),const_cast<long*>(&lOne),
           reinterpret_cast<double*>(v()),const_cast<long*>(&lOne));
  }

  void copy(Vector<double>& v, const Vector<UniqueParameter64Bit>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,
           reinterpret_cast<double*>(const_cast<UniqueParameter64Bit*>(cv())),
           const_cast<long*>(&lOne),v(),const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter64Bit>& v,
            const Vector<unsigned long long>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,reinterpret_cast<double*>(const_cast<unsigned long long*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<unsigned long long>& v,
            const Vector<UniqueParameter64Bit>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,
           reinterpret_cast<double*>(const_cast<UniqueParameter64Bit*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter64Bit>& v, const Vector<long long>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,reinterpret_cast<double*>(const_cast<long long*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<long long>& v, const Vector<UniqueParameter64Bit>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,
           reinterpret_cast<double*>(const_cast<UniqueParameter64Bit*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter64Bit>& v, const Vector<float>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,const_cast<float*>(cv()),const_cast<long*>(&lOne),
           reinterpret_cast<float*>(v()),const_cast<long*>(&lTwo));
  }

  void copy(Vector<float>& v, const Vector<UniqueParameter64Bit>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<UniqueParameter64Bit*>(cv())),
           const_cast<long*>(&lTwo),v(),const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter64Bit>& v, const Vector<int>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<int*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lTwo));
  }

  void copy(Vector<int>& v, const Vector<UniqueParameter64Bit>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<UniqueParameter64Bit*>(cv())),
           const_cast<long*>(&lTwo),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter64Bit>& v, const Vector<unsigned int>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<unsigned int*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lTwo));
  }

  void copy(Vector<unsigned int>& v, const Vector<UniqueParameter64Bit>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<UniqueParameter64Bit*>(cv())),
           const_cast<long*>(&lTwo),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

}

#endif
