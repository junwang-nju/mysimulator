
#ifndef _Array_1D_Content_Sum_H_
#define _Array_1D_Content_Sum_H_

#include "intrinsic-type/shift.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T>
  T _sum(T* p, const unsigned int& del, const unsigned int& n) {
    T sum;
    copy(sum,cZero);
    T* e=p+n*del;
    for(;p!=e;p+=del) shift(sum,*p);
  }

  template <typename T>
  T _sum(T* p, const unsigned int& n) {
    T sum;
    copy(sum,cZero);
    T* e=p+n;
    for(;p!=e;) shift(sum,*(p++));
  }

}

#include "linear-algebra/blas.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T>
  T _sum_blas(T* p, const unsigned int& del, const unsigned int& n) {
    return BLAS<T>::Dot(
        _LONG_POINTER(&n),p,_LONG_POINTER(&del),const_cast<T*>(&ValueOne<T>()),
        const_cast<long*>(&lZero));
  }

  template <typename T>
  T _sum_blas(T* p, const unsigned int& n) {
    return BLAS<T>::Dot(
        _LONG_POINTER(&n),p,const_cast<long*>(&lOne),
        const_cast<T*>(&ValueOne<T>()),const_cast<long*>(&lZero));
  }

}

#undef _LONG_POINTER

#define _SUM_WithDel(type) \
  type _sum(type* p, const unsigned int& del, const unsigned int& n) {\
    return _sum_blas(p,del,n);\
  }

#define _SUM(type) \
  type _sum(type* p, const unsigned int& n) { return _sum_blas(p,n); }

namespace mysimulator {

  _SUM_WithDel(double)
  _SUM_WithDel(float)
  _SUM(double)
  _SUM(float)

}

#undef _SUM
#undef _SUM_WithDel

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  T sum(const Array1DContent<T>& A, const int& fst, const unsigned int& del,
        const unsigned int& n) {
    assert(IsValid(A,fst,del,n));
    T* p=const_cast<T*>(A.head+fst);
    _sum(p,del,n);
  }

  template <typename T>
  T sum(const Array1DContent<T>& A, const int& fst, const unsigned int& n) {
    assert(IsValid(A,fst,n));
    T* p=const_cast<T*>(A.head+fst);
    _sum(p,n);
  }

  template <typename T>
  T sum(const Array1DContent<T>& A, const unsigned int& n) {
    assert(IsValid(A,n));
    T* p=const_cast<T*>(A.start);
    _sum(p,n);
  }

  template <typename T>
  T sum(const Array1DContent<T>& A) {
    assert(IsValid(A));
    T* p=const_cast<T*>(A.start);
    _sum(p,A.size);
  }

}

#endif

