
#ifndef _Array_1D_Content_ScaleShift_Three_H_
#define _Array_1D_Content_ScaleShift_Three_H_

#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3, typename T4, typename T5>
  void _sshift(T1* p, const T2& u, const T3& v, T4* q, T5* r,
               const unsigned int& d1, const unsigned int& d2,
               const unsigned int& d3, const unsigned int& n) {
    T1* e=p+d1*n;
    for(;p!=e;p+=d1,q+=d2,r+=d3)  scaleshift(*p,u,v,*q,*r);
  }

  template <typename T1, typename T2, typename T3, typename T4, typename T5>
  void _sshift(T1* p, const T2& u, const T3& v, T4* q, T5* r,
               const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;)  scaleshift(*(p++),u,v,*(q++),*(r++));
  }

}

#include "linear-algebra/blas.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/constant.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T1, typename T2, typename T3>
  void _sshift_blas(T1* p, const T2& u, const T3& v, T1* q, T1* r,
                    const unsigned int& d1, const unsigned int& d2,
                    const unsigned int& d3, const unsigned int& n) {
    T1 tu,tv;
    copy(tu,u);
    copy(tv,v);
    static char fg[]="L";
    BLAS<T1>::SbMv(
        fg,_LONG_POINTER(&n),const_cast<long*>(&lZero),&tv,q,_LONG_POINTER(&d2),
        r,_LONG_POINTER(&d3),&tu,p,_LONG_POINTER(&d1));
  }
  template <typename T1, typename T2, typename T3>
  void _sshift_blas(T1* p, const T2& u, const T3& v, T1* q, T1* r,
                    const unsigned int& n) {
    T1 tu,tv;
    copy(tu,u);
    copy(tv,v);
    static char fg[]="L";
    BLAS<T1>::SbMv(
        fg,_LONG_POINTER(&n),const_cast<long*>(&lZero),&tv,q,
        const_cast<long*>(&lOne),r,const_cast<long*>(&lOne),&tu,p,
        const_cast<long*>(&lOne));
  }

}

#undef _LONG_POINTER

#define _SSHIFTCVV_WithDel(type) \
  template <typename T1, typename T2>\
  void _sshift(type* p, const T1& u, const T2& v, type* q, type* r,\
               const unsigned int& d1, const unsigned int& d2,\
               const unsigned int& d3, const unsigned int& n) {\
    _sshift_blas(p,u,v,q,r,d1,d2,d3,n);\
  }

#define _SSHIFTCVV(type) \
  template <typename T1, typename T2>\
  void _sshift(type* p, const T1& u, const T2& v, type* q, type* r,\
               const unsigned int& n) {\
    _sshift_blas(p,u,v,q,r,n);\
  }

namespace mysimulator {

  _SSHIFTCVV_WithDel(double)
  _SSHIFTCVV(double)
  _SSHIFTCVV_WithDel(float)
  _SSHIFTCVV(float)

}

#undef _SSHIFTCVV
#undef _SSHIFTCVV_WithDel

#include "array/1d/content/interface.h"

#define _SSHIFT1(type1,type2) \
  template <typename T1, typename T2, typename T3>\
  void scaleshift(Array1DContent<T1>& A, const type1& u, const type2& v,\
                  const Array1DContent<T2>& B, const Array1DContent<T3>& C,\
                  const int& b1, const unsigned int& d1, const int& b2,\
                  const unsigned int& d2,const int& b3,const unsigned int& d3,\
                  const unsigned int& n) {\
    assert(IsValid(A,b1,d1,n)&&IsValid(B,b2,d2,n)&&IsValid(C,b3,d3,n));\
    T1* p=A.head+b1;\
    T2* q=const_cast<T2*>(B.head+b2);\
    T3* r=const_cast<T3*>(C.head+b3);\
    _sshift(p,u,v,q,r,d1,d2,d3,n);\
  }

#define _SSHIFT2(type1,type2) \
  template <typename T1, typename T2, typename T3>\
  void scaleshift(Array1DContent<T1>& A, const type1& u, const type2& v,\
                  const Array1DContent<T2>& B, const Array1DContent<T3>& C,\
                  const int& b1, const int& b2, const int& b3,\
                  const unsigned int& n) {\
    assert(IsValid(A,b1,n)&&IsValid(B,b2,n)&&IsValid(C,b3,n));\
    T1* p=A.head+b1;\
    T2* q=const_cast<T2*>(B.head+b2);\
    T3* r=const_cast<T3*>(C.head+b3);\
    _sshift(p,u,v,q,r,n);\
  }

#define _SSHIFT3(type1,type2) \
  template <typename T1, typename T2, typename T3>\
  void scaleshift(Array1DContent<T1>& A, const type1& u, const type2& v,\
                  const Array1DContent<T2>& B, const Array1DContent<T3>& C,\
                  const unsigned int& n) {\
    assert(IsValid(A,n)&&IsValid(B,n)&&IsValid(C,n));\
    T1* p=A.start;\
    T2* q=const_cast<T2*>(B.start);\
    T3* r=const_cast<T3*>(C.start);\
    _sshift(p,u,v,q,r,n);\
  }

#define _SSHIFT4(type1,type2) \
  template <typename T1, typename T2, typename T3>\
  void scaleshift(Array1DContent<T1>& A, const type1& u, const type2& v,\
                  const Array1DContent<T2>& B, const Array1DContent<T3>& C) {\
    assert(IsValid(A)&&IsValid(B)&&IsValid(C));\
    T1* p=A.start;\
    T2* q=const_cast<T2*>(B.start);\
    T3* r=const_cast<T3*>(C.start);\
    _sshift(p,u,v,q,r,((A.size<B.size)&&(A.size<C.size)?A.size:\
                       (B.size<C.size?B.size:C.size)));\
  }

#define _SSHIFT(type1,type2) \
  _SSHIFT1(type1,type2)\
  _SSHIFT2(type1,type2)\
  _SSHIFT3(type1,type2)\
  _SSHIFT4(type1,type2)

#define _SSHIFT_(type) \
  _SSHIFT(type, long double)\
  _SSHIFT(type, double)\
  _SSHIFT(type, float)\
  _SSHIFT(type, long long)\
  _SSHIFT(type, unsigned long long)\
  _SSHIFT(type, int)\
  _SSHIFT(type, unsigned int)\
  _SSHIFT(type, long)\
  _SSHIFT(type, unsigned long)\
  _SSHIFT(type, short)\
  _SSHIFT(type, unsigned short)\
  _SSHIFT(type, char)\
  _SSHIFT(type, unsigned char)

namespace mysimulator {

  _SSHIFT_(long double)
  _SSHIFT_(double)
  _SSHIFT_(float)
  _SSHIFT_(long long)
  _SSHIFT_(unsigned long long)
  _SSHIFT_(int)
  _SSHIFT_(unsigned int)
  _SSHIFT_(long)
  _SSHIFT_(unsigned long)
  _SSHIFT_(short)
  _SSHIFT_(unsigned short)
  _SSHIFT_(char)
  _SSHIFT_(unsigned char)

}

#undef _SSHIFT_
#undef _SSHIFT
#undef _SSHIFT4
#undef _SSHIFT3
#undef _SSHIFT2
#undef _SSHIFT1

#endif

