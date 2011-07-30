
#ifndef _Array_1D_Content_ScaleShift_Two_H_
#define _Array_1D_Content_ScaleShift_Two_H_

#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3, typename T4>
  void _sshift(T1* p, const T2& u, T3* q, T4* r, const unsigned int& d1,
               const unsigned int& d2, const unsigned int& d3,
               const unsigned int& n) {
    T1* e=p+d1*n;
    for(;p!=e;p+=d1,q+=d2,r+=d3)  scaleshift(*p,u,*q,*r);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  void _sshift(T1* p, const T2& u, T3* q, T4* r, const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;)  scaleshift(*(p++),u,*(q++),*(r++));
  }

}

#include "linear-algebra/blas.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/constant.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T1, typename T2>
  void _sshift_blas(T1* p, const T2& u, T1* q, T1& r, const unsigned int& d1,
                    const unsigned int& d2, const unsigned int& d3,
                    const unsigned int& n) {
    T1 tu;
    copy(tu,u);
    static char fg[]="L";
    BLAS<T1>::SbMv(
        fg,_LONG_POINTER(&n),const_cast<long*>(&lZero),
        const_cast<T1*>(&ValueOne<T1>()),q,_LONG_POINTER(&d2),r,
        _LONG_POINTER(&d3),&tu,p,_LONG_POINTER(&d1));
  }
  template <typename T1, typename T2>
  void _sshift_blas(T1* p, const T2& u, T1* q, T1& r, const unsigned int& n) {
    T1 tu;
    copy(tu,u);
    static char fg[]="L";
    BLAS<T1>::SbMv(
        fg,_LONG_POINTER(&n),const_cast<long*>(&lZero),
        const_cast<T1*>(&ValueOne<T1>()),q,const_cast<long*>(&lOne),r,
        const_cast<long*>(&lOne),&tu,p,const_cast<long*>(&lOne));
  }

}

#undef _LONG_POINTER

#define _SSHIFTVV_WithDel(type) \
  template <typename T>\
  void _sshift(type* p, const T& u,type* q,type* r,const unsigned int& d1,\
               const unsigned int& d2,const unsigned int& d3,\
               const unsigned int& n) { _sshift_blas(p,u,q,r,d1,d2,d3,n); }

#define _SSHIFTVV(type) \
  template <typename T>\
  void _sshift(type* p, const T& u,type* q,type* r,const unsigned int& n) {\
    _sshift_blas(p,u,q,r,n);\
  }

namespace mysimulator {

  _SSHIFTVV_WithDel(double)
  _SSHIFTVV(double)
  _SSHIFTVV_WithDel(float)
  _SSHIFTVV(float)

}

#undef _SSHIFTVV
#undef _SSHIFTVV_WithDel

#include "array/1d/content/interface.h"

#define _SSHIFT1(type) \
  template <typename T1, typename T2, typename T3>\
  void scaleshift(Array1DContent<T1>& A, const type& u,\
                  const Array1DContent<T2>& B, const Array1DContent<T3>& C,\
                  const int& b1, const unsigned int& d1, const int& b2,\
                  const unsigned int& d2, const int& b3,\
                  const unsigned int& d3, const unsigned int& n) {\
    assert(IsValid(A,b1,d1,n)&&IsValid(B,b2,d2,n)&&IsValid(C,b3,d3,n));\
    T1* p=A.head+b1;\
    T2* q=const_cast<T2*>(B.head+b2);\
    T3* r=const_cast<T3*>(C.head+b3);\
    _sshift(p,u,q,r,d1,d2,d3,n);\
  }

#define _SSHIFT2(type) \
  template <typename T1, typename T2, typename T3>\
  void scaleshift(Array1DContent<T1>& A, const type& u,\
                  const Array1DContent<T2>& B, const Array1DContent<T3>& C,\
                  const int& b1, const int& b2, const int& b3,\
                  const unsigned int& n) {\
    assert(IsValid(A,b1,n)&&IsValid(B,b2,n)&&IsValid(C,b3,n));\
    T1* p=A.head+b1;\
    T2* q=const_cast<T2*>(B.head+b2);\
    T3* r=const_cast<T3*>(C.head+b3);\
    _sshift(p,u,q,r,n);\
  }

#define _SSHIFT3(type) \
  template <typename T1, typename T2, typename T3>\
  void scaleshift(Array1DContent<T1>& A, const type& u,\
                  const Array1DContent<T2>& B, const Array1DContent<T3>& C,\
                  const unsigned int& n) {\
    assert(IsValid(A,n)&&IsValid(B,n)&&IsValid(C,n));\
    T1* p=A.start;\
    T2* q=const_cast<T2*>(B.start);\
    T3* r=const_cast<T3*>(C.start);\
    _sshift(p,u,q,r,n);\
  }

#define _SSHIFT4(type) \
  template <typename T1, typename T2, typename T3>\
  void scaleshift(Array1DContent<T1>& A, const type& u,\
                  const Array1DContent<T2>& B, const Array1DContent<T3>& C) {\
    assert(IsValid(A)&&IsValid(B)&&IsValid(C));\
    T1* p=A.start;\
    T2* q=const_cast<T2*>(B.start);\
    T3* r=const_cast<T3*>(C.start);\
    _sshift(p,u,q,r,((A.size<B.size)&&(A.size<C.size)?A.size:\
                     (B.size<C.size?B.size:C.size)));\
  }

#define _SSHIFT(type) \
  _SSHIFT1(type)\
  _SSHIFT2(type)\
  _SSHIFT3(type)\
  _SSHIFT4(type)

namespace mysimulator {

  _SSHIFT(long double)
  _SSHIFT(double)
  _SSHIFT(float)
  _SSHIFT(long long)
  _SSHIFT(unsigned long long)
  _SSHIFT(int)
  _SSHIFT(unsigned int)
  _SSHIFT(long)
  _SSHIFT(unsigned long)
  _SSHIFT(short)
  _SSHIFT(unsigned short)
  _SSHIFT(char)
  _SSHIFT(unsigned char)

}

#undef _SSHIFT
#undef _SSHIFT4
#undef _SSHIFT3
#undef _SSHIFT2
#undef _SSHIFT1

#endif

