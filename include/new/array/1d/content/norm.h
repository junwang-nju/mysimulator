
#ifndef _Array_1D_Content_Norm_H_
#define _Array_1D_Content_Norm_H_

#include "array/1d/content/dot.h"

namespace mysimulator {

  template <typename T>
  T normSQ(const Array1DContent<T>& A, const int& fst, const unsigned int& del,
           const unsigned int& n) { return dot(A,A,fst,del,fst,del,n); }

  template <typename T>
  T normSQ(const Array1DContent<T>& A, const int& fst, const unsigned int& n) {
    return dot(A,A,fst,fst,n);
  }

  template <typename T>
  T normSQ(const Array1DContent<T>& A, const unsigned int& n) {
    return dot(A,A,n);
  }

  template <typename T>
  T normSQ(const Array1DContent<T>& A) { return dot(A,A); }

}

#include <cmath>

namespace mysimulator {

  long double norm(const Array1DContent<long double>& A, const int& fst,
                   const unsigned int& del, const unsigned int& n) {
    return sqrtl(normSQ(A,fst,del,n));
  }

  long double norm(const Array1DContent<long double>& A, const int& fst,
                   const unsigned int& n) {
    return sqrtl(normSQ(A,fst,n));
  }

  long double norm(const Array1DContent<long double>& A, const unsigned int& n){
    return sqrtl(normSQ(A,n));
  }

  long double norm(const Array1DContent<long double>& A) {
    return sqrtl(normSQ(A));
  }

}

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T>
  T _norm_blas(T* p, const unsigned int& del, const unsigned int& n) {
    return BLAS<T>::Norm(_LONG_POINTER(&n),p,_LONG_POINTER(&del));
  }

  template <typename T>
  T _norm_blas(T* p, const unsigned int& n) {
    return BLAS<T>::Norm(_LONG_POINTER(&n),p,const_cast<long*>(&lOne));
  }

}

#undef _LONG_POINTER

#define _NORM_WithDel(type) \
  type _norm(type* p, const unsigned int& del, const unsigned int& n) {\
    return _norm_blas(p,del,n);\
  }

#define _NORM(type) \
  type _norm(type* p, const unsigned int& n) { return _norm_blas(p,n); }

namespace mysimulator {

  _NORM_WithDel(double)
  _NORM_WithDel(float)

  _NORM(double)
  _NORM(float)

}

#undef _NORM
#undef _NORM_WithDel

namespace mysimulator {

  template <typename T>
  T norm(const Array1DContent<T>& A, const int& fst, const unsigned int& del,
         const unsigned int& n) {
    assert(IsValid(A,fst,del,n));
    T* p=A.head+fst;
    return _norm(p,del,n);
  }

  template <typename T>
  T norm(const Array1DContent<T>& A, const int& fst, const unsigned int& n) {
    assert(IsValid(A,fst,n));
    T* p=A.head+fst;
    return _norm(p,n);
  }

  template <typename T>
  T norm(const Array1DContent<T>& A, const unsigned int& n) {
    assert(IsValid(A,n));
    T* p=A.start;
    return _norm(p,n);
  }

  template <typename T>
  T norm(const Array1DContent<T>& A) {
    assert(IsValid(A));
    T* p=A.start;
    return _norm(p,A.size);
  }

}

#endif

