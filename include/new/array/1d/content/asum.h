
#ifndef _Array_1D_Content_ASum_H_
#define _Array_1D_Content_ASum_H_

#include "intrinsic-type/copy.h"
#include "intrinsic-type/shift.h"
#include "intrinsic-type/constant.h"
#include "intrinsic-type/abs-value.h"

namespace mysimulator {

  template <typename T>
  T _asum(T* p, const unsigned int& del, const unsigned int& n) {
    T sum;
    copy(sum,cZero);
    T* e=p+n*del;
    for(;p!=e;p+=del) shift(sum,absval(*p));
    return sum;
  }

  template <typename T>
  T _asum(T* p, const unsigned int& n) {
    T sum;
    copy(sum,cZero);
    T* e=p+n;
    for(;p!=e;) shift(sum,absval(*(p++)));
    return sum;
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  template <typename T>
  T _asum_blas(T* p, const unsigned int& del, const unsigned int& n) {
    return BLAS<T>::ASum(
        reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
        p,reinterpret_cast<long*>(const_cast<unsigned int*>(&del)));
  }

  template <typename T>
  T _asum_blas(T* p, const unsigned int& n) {
    return BLAS<T>::ASum(
        reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
        p,const_cast<long*>(&lOne));
  }

}

#define _ASUM_WithDel(type) \
  type _asum(type* p, const unsigned int& del, const unsigned int& n) {\
    return _asum_blas(p,del,n);\
  }

#define _ASUM(type) \
  type _asum(type* p, const unsigned int& n) { return _asum_blas(p,n); }

namespace mysimulator {

  _ASUM_WithDel(double)
  _ASUM(double)
  _ASUM_WithDel(float)
  _ASUM(float)

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  T asum(const Array1DContent<T>& A, const int& fst,
         const unsigned int& del, const unsigned int& n) {
    assert(IsValid(A,fst,del,n));
    T* p=A.head+fst;
    return _asum(p,del,n);
  }

  template <typename T>
  T asum(const Array1DContent<T>& A, const int& fst,
         const unsigned int& n) {
    assert(IsValid(A,fst,n));
    T* p=A.head+fst;
    return _asum(p,n);
  }

  template <typename T>
  T asum(const Array1DContent<T>& A, const unsigned int& n) {
    assert(IsValid(A,n));
    T* p=A.start;
    return _asum(p,n);
  }

  template <typename T>
  T asum(const Array1DContent<T>& A) {
    assert(IsValid(A));
    T* p=A.start;
    return _asum(p,A.size);
  }

}

#endif

