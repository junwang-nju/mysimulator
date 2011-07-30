
#ifndef _Array_1D_Content_Dot_H_
#define _Array_1D_Content_Dot_H_

#define _DotTYPE(T1,T2)  typename _Dual<T1,T2>::CombineType

#include "intrinsic-type/shift.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/constant.h"
#include "intrinsic-type/reflection/dual.h"

namespace mysimulator {

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  _dot(T1* p, T2* q, const unsigned int& n,
       const unsigned int& d1, const unsigned int& d2) {
    T1* e=p+n*d1;
    _DotTYPE(T1,T2)  sum;
    copy(sum,cZero);
    for(;p!=e;p+=d1,q+=d2)  shift(sum,*p,*q);
    return sum;
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  _dot(T1* p, T2* q, const unsigned int& n) {
    T1* e=p+n;
    _DotTYPE(T1,T2)  sum;
    copy(sum,cZero);
    for(;p!=e;) shift(sum,*(p++),*(q++));
    return sum;
  }

}

#include "linear-algebra/blas.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T>
  T _dot_blas(T* p, T* q, const unsigned int& n,
              const unsigned int& d1, const unsigned int& d2) {
    return BLAS<T>::Dot(
        _LONG_POINTER(&n),p,_LONG_POINTER(&d1),q,_LONG_POINTER(&d2));
  }

  template <typename T>
  T _dot_blas(T* p, T* q, const unsigned int& n) {
    return BLAS<T>::Dot(
        _LONG_POINTER(&n),p,const_cast<long*>(&lOne),q,
        const_cast<long*>(&lOne));
  }

}

#undef _LONG_POINTER

#define _DOT_WithDel(type) \
  type _dot(type* p, type* q, const unsigned int& n,\
            const unsigned int& d1, const unsigned int& d2) {\
    return _dot_blas(p,q,n,d1,d2);\
  }

#define _DOT(type) \
  type _dot(type* p,type* q,const unsigned int& n) { return _dot_blas(p,q,n); }

namespace mysimulator {

  _DOT_WithDel(double)
  _DOT_WithDel(float)

  _DOT(double)
  _DOT(float)

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array1DContent<T1>& A1, const Array1DContent<T2>& A2,
      const int& b1, const unsigned int& d1, const int& b2,
      const unsigned int& d2, const unsigned int& n) {
    assert(IsValid(A1,b1,d1,n)&&IsValid(A2,b2,d2,n));
    T1* p=const_cast<T1*>(A1.head+b1);
    T2* q=const_cast<T2*>(A2.head+b2);
    return _dot(p,q,n,d1,d2);
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array1DContent<T1>& A1, const Array1DContent<T2>& A2,
      const int& b1, const int& b2, const unsigned int& n) {
    assert(IsValid(A1,b1,n)&&IsValid(A2,b2,n));
    T1* p=const_cast<T1*>(A1.head+b1);
    T2* q=const_cast<T2*>(A2.head+b2);
    return _dot(p,q,n);
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array1DContent<T1>& A1, const Array1DContent<T2>& A2,
      const unsigned int& n) {
    assert(IsValid(A1,n)&&IsValid(A2,n));
    T1* p=const_cast<T1*>(A1.start);
    T2* q=const_cast<T2*>(A2.start);
    return _dot(p,q,n);
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array1DContent<T1>& A1, const Array1DContent<T2>& A2) {
    assert(IsValid(A1)&&IsValid(A2));
    T1* p=const_cast<T1*>(A1.start);
    T2* q=const_cast<T2*>(A2.start);
    return _dot(p,q,(A1.size<A2.size?A1.size:A2.size));
  }

}

#undef _DotTYPE

#endif

