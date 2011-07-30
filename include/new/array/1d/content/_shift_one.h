
#ifndef _Array_1D_Content_SHIFT_One_H_
#define _Array_1D_Content_SHIFT_One_H_

#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _shift(T1* p,const T2& u,const unsigned int& d1,const unsigned int& n) {
    T1* e=p+d1*n;
    for(;p!=e;p+=d1)  shift(*p,u);
  }
  template <typename T1, typename T2>
  void _shift(T1* p,const T2& u,const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;) shift(*(p++),u);
  }

  template <typename T1, typename T2>
  void _shift(T1* p, T2* q, const unsigned int& d1, const unsigned int& d2,
              const unsigned int& n) {
    T1* e=p+d1*n;
    for(;p!=e;p+=d1,q+=d2)  shift(*p,*q);
  }
  template <typename T1, typename T2>
  void _shift(T1* p, T2* q, const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;) shift(*(p++),*(q++));
  }

}

#include "linear-algebra/blas.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/constant.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T1, typename T2>
  void _shift_blas(T1* p, const T2& u, const unsigned int& d1,
                   const unsigned int& n) {
    T1 tu;
    copy(tu,u);
    BLAS<T1>::Shift(
        _LONG_POINTER(&n),const_cast<T1*>(&ValueOne<T1>()),&tu,
        const_cast<long*>(&lZero),p,_LONG_POINTER(&d1));
  }
  template <typename T1, typename T2>
  void _shift_blas(T1* p, const T2& u, const unsigned int& n) {
    T1 tu;
    copy(tu,u);
    BLAS<T1>::Shift(
        _LONG_POINTER(&n),const_cast<T1*>(&ValueOne<T1>()),&tu,
        const_cast<long*>(&lZero),p,const_cast<long*>(&lOne));
  }

  template <typename T>
  void _shift_blas(T* p, T* q, const unsigned int& d1, const unsigned int& d2,
                   const unsigned int& n) {
    BLAS<T>::Shift(
        _LONG_POINTER(&n),const_cast<T*>(&ValueOne<T>()),q,
        _LONG_POINTER(&d2),p,_LONG_POINTER(&d1));
  }
  template <typename T>
  void _shift_blas(T* p, T* q, const unsigned int& n) {
    BLAS<T>::Shift(
        _LONG_POINTER(&n),const_cast<T*>(&ValueOne<T>()),q,
        const_cast<long*>(&lOne),p,const_cast<long*>(&lOne));
  }

}

#undef _LONG_POINTER

#define _SHIFTC_WithDel(type) \
  template <typename T>\
  void _shift(type* p, const T& u, const unsigned int& d1,\
              const unsigned int& n) { _shift_blas(p,u,d1,n); }

#define _SHIFTC(type) \
  template <typename T>\
  void _shift(type* p, const T& u, const unsigned int& n) {\
    _shift_blas(p,u,n);\
  }

#define _SHIFTV_WithDel(type) \
  void _shift(type* p, type* q, const unsigned int& d1, const unsigned int& d2,\
              const unsigned int& n) { _shift_blas(p,q,d1,d2,n); }

#define _SHIFTV(type) \
  void _shift(type* p, type* q, const unsigned int& n) { _shift_blas(p,q,n); }

namespace mysimulator {

  _SHIFTC_WithDel(double)
  _SHIFTC(double)

  _SHIFTC_WithDel(float)
  _SHIFTC(float)

  _SHIFTV_WithDel(double)
  _SHIFTV(double)

  _SHIFTV_WithDel(float)
  _SHIFTV(float)

}

#undef _SHIFTV
#undef _SHIFTV_WithDel
#undef _SHIFTC
#undef _SHIFTC_WithDel

#include "array/1d/content/interface.h"

#define _SHIFT1(type) \
  template <typename T>\
  void shift(Array1DContent<T>& A, const type& u, const int& b1,\
             const unsigned int& d1, const unsigned int& n) {\
    assert(IsValid(A,b1,d1,n));\
    T* p=A.head+b1; _shift(p,u,d1,n);\
  }

#define _SHIFT2(type) \
  template <typename T>\
  void shift(Array1DContent<T>& A, const type& u, const int& b1,\
             const unsigned int& n) {\
    assert(IsValid(A,b1,n));\
    T* p=A.head+b1; _shift(p,u,n);\
  }

#define _SHIFT3(type) \
  template <typename T>\
  void shift(Array1DContent<T>& A, const type& u, const unsigned int& n) {\
    assert(IsValid(A,n));\
    T* p=A.start;   _shift(p,u,n);\
  }

#define _SHIFT4(type) \
  template <typename T>\
  void shift(Array1DContent<T>& A, const type& u) {\
    assert(IsValid(A));\
    T* p=A.start;   _shift(p,u,A.size);\
  }

#define _SHIFT(type) \
  _SHIFT1(type)\
  _SHIFT2(type)\
  _SHIFT3(type)\
  _SHIFT4(type)

namespace mysimulator {

  _SHIFT(long double)
  _SHIFT(double)
  _SHIFT(float)
  _SHIFT(long long)
  _SHIFT(unsigned long long)
  _SHIFT(int)
  _SHIFT(unsigned int)
  _SHIFT(long)
  _SHIFT(unsigned long)
  _SHIFT(short)
  _SHIFT(unsigned short)
  _SHIFT(char)
  _SHIFT(unsigned char)

}

#undef _SHIFT
#undef _SHIFT1
#undef _SHIFT2
#undef _SHIFT3
#undef _SHIFT4

namespace mysimulator {

  template <typename T1, typename T2>
  void shift(Array1DContent<T1>& A1, const Array1DContent<T2>& A2,
             const int& b1, const unsigned int& d1, const int& b2,
             const unsigned int& d2, const unsigned int& n) {
    assert(IsValid(A1,b1,d1,n)&&IsValid(A2,b2,d2,n));
    T1* p=A1.head+b1;
    T2* q=A2.head+b2;
    _shift(p,q,d1,d2,n);
  }

  template <typename T1, typename T2>
  void shift(Array1DContent<T1>& A1, const Array1DContent<T2>& A2,
             const int& b1, const int& b2, const unsigned int& n) {
    assert(IsValid(A1,b1,n)&&IsValid(A2,b2,n));
    T1* p=A1.head+b1;
    T2* q=A2.head+b2;
    _shift(p,q,n);
  }

  template <typename T1, typename T2>
  void shift(Array1DContent<T1>& A1, const Array1DContent<T2>& A2,
             const unsigned int& n) {
    assert(IsValid(A1,n)&&IsValid(A2,n));
    T1* p=A1.start;
    T2* q=A2.start;
    _shift(p,q,n);
  }

  template <typename T1, typename T2>
  void shift(Array1DContent<T1>& A1, const Array1DContent<T2>& A2) {
    assert(IsValid(A1)&&IsValid(A2));
    T1* p=A1.start;
    T2* q=A2.start;
    _shift(p,q,(A1.size<A2.size?A1.size:A2.size));
  }

}

#endif

