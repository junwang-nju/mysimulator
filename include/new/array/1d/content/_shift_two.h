
#ifndef _Array_1D_Content_SHIFT_Two_H_
#define _Array_1D_Content_SHIFT_Two_H_

#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3>
  void _shift(T1* p, const T2& u, T3* q, const unsigned int& d1,
              const unsigned int& d2, const unsigned int& n) {
    T1* e=p+d1*n;
    for(;p!=e;p+=d1,q+=d2)  shift(*p,u,*q);
  }
  template <typename T1, typename T2, typename T3>
  void _shift(T1* p, const T2& u, T3* q, const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;) shift(*(p++),u,*(q++));
  }

  template <typename T1, typename T2, typename T3>
  void _shift(T1* p, T2* q, T3* r, const unsigned int& d1,
              const unsigned int& d2, const unsigned int& d3,
              const unsigned int& n) {
    T1* e=p+d1*n;
    for(;p!=e;p+=d1,q+=d2,r+=d3)  shift(*p,*q,*r);
  }
  template <typename T1, typename T2, typename T3>
  void _shift(T1* p, T2* q, T3* r, const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;)  shift(*(p++),*(q++),*(r++));
  }

}

#include "linear-algebra/blas.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/constant.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T1, typename T2>
  void _shift_blas(T1* p, const T2& u, T1* q, const unsigned int& d1,
                   const unsigned int& d2, const unsigned int& n) {
    T1 tu;
    copy(tu,u);
    BLAS<T1>::Shift(
        _LONG_POINTER(&n),&tu,q,_LONG_POINTER(&d2),p,_LONG_POINTER(&d1));
  }
  template <typename T1, typename T2>
  void _shift_blas(T1* p, const T2& u, T1* q, const unsigned int& n) {
    T1 tu;
    copy(tu,u);
    BLAS<T1>::Shift(
        _LONG_POINTER(&n),&tu,q,const_cast<long*>(&lOne),p,
        const_cast<long*>(&lOne));
  }

  template <typename T>
  void _shift_blas(T* p, T* q, T* r, const unsigned int& d1,
                   const unsigned int& d2, const unsigned int& d3,
                   const unsigned int& n) {
    static char fg[]="L";
    BLAS<T>::SbMv(
       fg,_LONG_POINTER(&n),const_cast<long*>(&lZero),
       const_cast<T*>(&ValueOne<T>()),q,_LONG_POINTER(&d2),r,_LONG_POINTER(&d3),
       const_cast<T*>(&ValueOne<T>()),p,_LONG_POINTER(&d1));
  }
  template <typename T>
  void _shift_blas(T* p, T* q, T* r, const unsigned int& n) {
    static char fg[]="L";
    BLAS<T>::SbMv(
        fg,_LONG_POINTER(&n),const_cast<long*>(&lZero),
        const_cast<T*>(&ValueOne<T>()),q,const_cast<long*>(&lOne),r,
        const_cast<long*>(&lOne),const_cast<T*>(&ValueOne<T>()),p,
        const_cast<long*>(&lOne));
  }

}

#undef _LONG_POINTER

#define _SHIFTCV_WithDel(type) \
  template <typename T>\
  void _shift(type* p, const T& u, type* q, const unsigned int& d1,\
              const unsigned int& d2, const unsigned int& n) {\
    _shift_blas(p,u,q,d1,d2,n);\
  }

#define _SHIFTCV(type) \
  template <typename T>\
  void _shift(type* p, const T& u, type* q, const unsigned int& n) {\
    _shift_blas(p,u,q,n);\
  }

#define _SHIFTVV_WithDel(type) \
  void _shift(type* p,type* q,type* r, const unsigned int& d1,\
              const unsigned int& d2, const unsigned int& d3,\
              const unsigned int& n) { _shift_blas(p,q,r,d1,d2,d3,n); }

#define _SHIFTVV(type) \
  void _shift(type* p,type* q,type* r, const unsigned int& n) {\
    _shift_blas(p,q,r,n);\
  }

namespace mysimulator {

  _SHIFTCV_WithDel(double)
  _SHIFTCV(double)
  _SHIFTCV_WithDel(float)
  _SHIFTCV(float)

  _SHIFTVV_WithDel(double)
  _SHIFTVV(double)
  _SHIFTVV_WithDel(float)
  _SHIFTVV(float)

}

#undef _SHIFTVV
#undef _SHIFTVV_WithDel
#undef _SHIFTCV
#undef _SHIFTCV_WithDel

#include "array/1d/content/interface.h"

#define _SHIFT1(type) \
  template <typename T1, typename T2>\
  void shift(Array1DContent<T1>& A,const type& u,const Array1DContent<T2>& B,\
             const int& b1, const unsigned int& d1, const int& b2,\
             const unsigned int& d2, const unsigned int& n) {\
    assert(IsValid(A,b1,d1,n)&&IsValid(B,b2,d2,n));\
    T1* p=A.head+b1;\
    T2* q=const_cast<T2*>(B.head+b2);\
    _shift(p,u,q,d1,d2,n);\
  }

#define _SHIFT2(type) \
  template <typename T1, typename T2>\
  void shift(Array1DContent<T1>& A,const type& u,const Array1DContent<T2>& B,\
             const int& b1, const int& b2, const unsigned int& n) {\
    assert(IsValid(A,b1,n)&&IsValid(B,b2,n));\
    T1* p=A.head+b1;\
    T2* q=const_cast<T2*>(B.head+b2);\
    _shift(p,u,q,n);\
  }

#define _SHIFT3(type) \
  template <typename T1, typename T2>\
  void shift(Array1DContent<T1>& A,const type& u,const Array1DContent<T2>& B,\
             const unsigned int& n) {\
    assert(IsValid(A,n)&&IsValid(B,n));\
    T1* p=A.start;\
    T2* q=const_cast<T2*>(B.start);\
    _shift(p,u,q,n);\
  }

#define _SHIFT4(type) \
  template <typename T1, typename T2>\
  void shift(Array1DContent<T1>& A,const type& u,const Array1DContent<T2>& B) {\
    assert(IsValid(A)&&IsValid(B));\
    T1* p=A.start;\
    T2* q=const_cast<T2*>(B.start);\
    _shift(p,u,q,(A.size<B.size?A.size:B.size));\
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
#undef _SHIFT4
#undef _SHIFT3
#undef _SHIFT2
#undef _SHIFT1

namespace mysimulator {

  template <typename T1, typename T2, typename T3>
  void shift(Array1DContent<T1>& A, const Array1DContent<T2>& B,\
             const Array1DContent<T3>& C, const int& b1, const unsigned int& d1,
             const int& b2, const unsigned int& d2, const int& b3,
             const unsigned int& d3, const unsigned int& n) {
    assert(IsValid(A,b1,d1,n)&&IsValid(B,b2,d2,n)&&IsValid(C,b3,d3,n));
    T1* p=A.head+b1;
    T2* q=const_cast<T2*>(B.head+b2);
    T3* r=const_cast<T3*>(C.head+b3);
    _shift(p,q,r,d1,d2,d3,n);
  }

  template <typename T1, typename T2, typename T3>
  void shift(Array1DContent<T1>& A, const Array1DContent<T2>& B,\
             const Array1DContent<T3>& C, const int& b1, const int& b2,
             const int& b3, const unsigned int& n) {
    assert(IsValid(A,b1,n)&&IsValid(B,b2,n)&&IsValid(C,b3,n));
    T1* p=A.head+b1;
    T2* q=const_cast<T2*>(B.head+b2);
    T3* r=const_cast<T3*>(C.head+b3);
    _shift(p,q,r,n);
  }

  template <typename T1, typename T2, typename T3>
  void shift(Array1DContent<T1>& A, const Array1DContent<T2>& B,\
             const Array1DContent<T3>& C, const unsigned int& n) {
    assert(IsValid(A,n)&&IsValid(B,n)&&IsValid(C,n));
    T1* p=A.start;
    T2* q=const_cast<T2*>(B.start);
    T3* r=const_cast<T3*>(C.start);
    _shift(p,q,r,n);
  }

  template <typename T1, typename T2, typename T3>
  void shift(Array1DContent<T1>& A, const Array1DContent<T2>& B,\
             const Array1DContent<T3>& C) {
    assert(IsValid(A)&&IsValid(B)&&IsValid(C));
    T1* p=A.start;
    T2* q=const_cast<T2*>(B.start);
    T3* r=const_cast<T3*>(C.start);
    _shift(p,q,r,((A.size<B.size)&&(A.size<C.size)?A.size:
                  (B.size<C.size?B.size:C.size)));
  }

}

#endif

