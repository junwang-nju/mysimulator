
#ifndef _Array_1D_Content_SHIFT_Three_H_
#define _Array_1D_Content_SHIFT_Three_H_

#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3, typename T4>
  void _shift(T1* p, const T2& u, T3* q, T4*r, const unsigned int& d1,
              const unsigned int& d2, const unsigned int& d3,
              const unsigned int& n) {
    T1* e=p+d1*n;
    for(;p!=e;p+=d1,q+=d2,r+=d3)  shift(*p,u,*q,*r);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  void _shift(T1* p, const T2& u, T3* q, T4*r, const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;) shift(*(p++),u,*(q++),*(r++));
  }

}

#include "linear-algebra/blas.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/constant.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T1, typename T2>
  void _shift_blas(T1* p, const T2& u, T1* q, T1* r, const unsigned int& d1,
                   const unsigned int& d2, const unsigned int& d3,
                   const unsigned int& n) {
    T1 tu;
    copy(tu,u);
    static char fg[]="L";
    BLAS<T1>::SbMv(
        fg,_LONG_POINTER(&n),const_cast<long*>(&lZero),&tu,q,_LONG_POINTER(&d2),
        r,_LONG_POINTER(&d3),const_cast<T1*>(&ValueOne<T1>()),p,
        _LONG_POINTER(&d1));
  }

  template <typename T1, typename T2>
  void _shift_blas(T1* p, const T2& u, T1* q, T1* r, const unsigned int& n) {
    T1 tu;
    copy(tu,u);
    static char fg[]="L";
    BLAS<T1>::SbMv(
        fg,_LONG_POINTER(&n),const_cast<long*>(&lZero),&tu,q,
        const_cast<long*>(&lOne),r,const_cast<long*>(&lOne),
        const_cast<T1*>(&ValueOne<T1>()),p,const_cast<long*>(&lOne));
  }

}

#define _SHIFTCVV_WithDel(type) \
  template <typename T>\
  void _shift(type* p, const T& u, type* q, type* r, const unsigned int& d1,\
              const unsigned int& d2, const unsigned int& d3,\
              const unsigned int& n) { _shift_blas(p,u,q,r,d1,d2,d3,n); }

#define _SHIFTCVV(type) \
  template <typename T>\
  void _shift(type* p, const T& u, type* q, type* r, const unsigned int& n) {\
    _shift_blas(p,u,q,r,n);\
  }

namespace mysimulator {

  _SHIFTCVV_WithDel(double)
  _SHIFTCVV(double)
  _SHIFTCVV_WithDel(float)
  _SHIFTCVV(float)

}

#undef _SHIFTCVV
#undef _SHIFTCVV_WithDel

#include "array/1d/content/interface.h"

#define _SHIFT1(type) \
  template <typename T1, typename T2, typename T3>\
  void shift(Array1DContent<T1>& A,const type& u,const Array1DContent<T2>& B,\
             const Array1DContent<T3>& C,const int& b1,const unsigned int& d1,\
             const int& b2,const unsigned int& d2,const int& b3,\
             const unsigned int& d3, const unsigned int& n) {\
    assert(IsValid(A,b1,d1,n)&&IsValid(B,b2,d2,n)&&IsValid(C,b3,d3,n));\
    T1* p=A.head+b1;\
    T2* q=const_cast<T2*>(B.head+b2);\
    T3* r=const_cast<T3*>(C.head+b3);\
    _shift(p,u,q,r,d1,d2,d3,n);\
  }

#define _SHIFT2(type) \
  template <typename T1, typename T2, typename T3>\
  void shift(Array1DContent<T1>& A,const type& u,const Array1DContent<T2>& B,\
             const Array1DContent<T3>& C,const int& b1,const int& b2,\
             const int& b3, const unsigned int& n) {\
    assert(IsValid(A,b1,n)&&IsValid(B,b2,n)&&IsValid(C,b3,n));\
    T1* p=A.head+b1;\
    T2* q=const_cast<T2*>(B.head+b2);\
    T3* r=const_cast<T3*>(C.head+b3);\
    _shift(p,u,q,r,n);\
  }

#define _SHIFT3(type) \
  template <typename T1, typename T2, typename T3>\
  void shift(Array1DContent<T1>& A,const type& u,const Array1DContent<T2>& B,\
             const Array1DContent<T3>& C,const unsigned int& n) {\
    assert(IsValid(A,n)&&IsValid(B,n)&&IsValid(C,n));\
    T1* p=A.start;\
    T2* q=const_cast<T2*>(B.start);\
    T3* r=const_cast<T3*>(C.start);\
    _shift(p,u,q,r,n);\
  }

#define _SHIFT4(type) \
  template <typename T1, typename T2, typename T3>\
  void shift(Array1DContent<T1>& A,const type& u,const Array1DContent<T2>& B,\
             const Array1DContent<T3>& C) {\
    assert(IsValid(A)&&IsValid(B)&&IsValid(C));\
    T1* p=A.start;\
    T2* q=const_cast<T2*>(B.start);\
    T3* r=const_cast<T3*>(C.start);\
    _shift(p,u,q,r,((A.size<B.size)&&(A.size<C.size)?A.size:\
                    (B.size<C.size?B.size:C.size)));\
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

#endif

