
#ifndef _Array_1D_Content_Scale_H_
#define _Array_1D_Content_Scale_H_

#include "intrinsic-type/scale.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _scale(T1* p, const T2& q, const unsigned int& del,
              const unsigned int& n) {
    T1* e=p+n*del;
    for(;p!=e;p+=del)  scale(*p,q);
  }

  template <typename T1, typename T2>
  void _scale(T1* p, const T2& q, const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;) scale(*(p++),q);
  }

  template <typename T1, typename T2>
  void _scale(T1* p, T2* q, const unsigned int& d1, const unsigned int d2,
              const unsigned int& n) {
    T1* e=p+n*d1;
    for(;p!=e;p+=d1,q+=d2)  scale(*p,*q);
  }

  template <typename T1, typename T2>
  void _scale(T1* p, T2* q, const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;) scale(*(p++),*(q++));
  }

}

#include "linear-algebra/blas.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/constant.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T>
  void _scale_blas(T* p, const T& q, const unsigned int& del,
                   const unsigned int& n) {
    T rq;
    copy(rq,q);
    BLAS<T>::Scale(_LONG_POINTER(&n),&rq,p,_LONG_POINTER(&del));
  }

  template <typename T>
  void _scale_blas(T* p, const T& q, const unsigned int& n) {
    T rq;
    copy(rq,q);
    BLAS<T>::Scale(_LONG_POINTER(&n),&rq,p,const_cast<long*>(&lOne));
  }

  template <typename T>
  void _scale_blas(T* p, T* q, const unsigned int& d1, const unsigned int& d2,
                   const unsigned int& n) {
    static char fg[]="LNN";
    BLAS<T>::TbMv(
        fg,fg+1,fg+2,_LONG_POINTER(&n),const_cast<long*>(&lZero),
        q,_LONG_POINTER(&d2),p,_LONG_POINTER(&d1));
  }

  template <typename T>
  void _scale_blas(T* p, T* q, const unsigned int& n) {
    static char fg[]="LNN";
    BLAS<T>::TbMv(
        fg,fg+1,fg+2,_LONG_POINTER(&n),const_cast<long*>(&lZero),q,
        const_cast<long*>(&lOne),p,const_cast<long*>(&lOne));
  }

}

#undef _LONG_POINTER

#define _SCALEC_WithDel(type) \
  template <typename T>\
  void _scale(type* p, const T& q, const unsigned int& del,\
              const unsigned int& n) {\
    type rq;\
    copy(rq,q);\
    _scale_blas(p,rq,del,n);\
  }

#define _SCALEC(type) \
  template <typename T>\
  void _scale(type* p,const T& q,const unsigned int& n) {\
    type rq;\
    copy(rq,q);\
    _scale_blas(p,rq,n);\
  }

#define _SCALEV_WithDel(type) \
  void _scale(type* p, type* q, const unsigned int& d1, const unsigned int& d2,\
              const unsigned int& n) { _scale_blas(p,q,d1,d2,n); }

#define _SCALEV(type) \
  void _scale(type* p, type* q, const unsigned int& n) { _scale_blas(p,q,n); }

namespace mysimulator {

  _SCALEC_WithDel(double)
  _SCALEC_WithDel(float)

  _SCALEC(double)
  _SCALEC(float)

  _SCALEV_WithDel(double)
  _SCALEV_WithDel(float)

  _SCALEV(double)
  _SCALEV(float)

}

#undef _SCALEV
#undef _SCALEV_WithDel
#undef _SCALEC
#undef _SCALEC_WithDel

#include "array/1d/content/interface.h"
#include "intrinsic-type/valid.h"

#define _SCALE1_CONST(type) \
  template <typename T>\
  void scale(Array1DContent<T>& A, const type& d, const int& fst,\
             const unsigned int& del, const unsigned int& n) {\
    assert(IsValid(A,fst,del,n));\
    T* p=A.head+fst;\
    _scale(p,d,del,n);\
  }

#define _SCALE2_CONST(type) \
  template <typename T>\
  void scale(Array1DContent<T>& A, const type& d, const int& fst,\
             const unsigned int& n) {\
    assert(IsValid(A,fst,n));\
    T* p=A.head+fst;\
    _scale(p,d,n);\
  }

#define _SCALE3_CONST(type) \
  template <typename T>\
  void scale(Array1DContent<T>& A, const type& d, const unsigned int& n) {\
    assert(IsValid(A,n));\
    T* p=A.start;\
    _scale(p,d,n);\
  }

#define _SCALE4_CONST(type) \
  template <typename T>\
  void scale(Array1DContent<T>& A, const type& d) {\
    assert(IsValid(A));\
    T* p=A.start;\
    _scale(p,d,A.size);\
  }

#define _SCALE_CONST(type) \
  _SCALE1_CONST(type)\
  _SCALE2_CONST(type)\
  _SCALE3_CONST(type)\
  _SCALE4_CONST(type)

namespace mysimulator {

  _SCALE_CONST(long double)
  _SCALE_CONST(double)
  _SCALE_CONST(float)
  _SCALE_CONST(long long)
  _SCALE_CONST(unsigned long long)
  _SCALE_CONST(int)
  _SCALE_CONST(unsigned int)
  _SCALE_CONST(long)
  _SCALE_CONST(unsigned long)
  _SCALE_CONST(short)
  _SCALE_CONST(unsigned short)
  _SCALE_CONST(char)
  _SCALE_CONST(unsigned char)

}

#undef _SCALE_CONST
#undef _SCALE4_CONST
#undef _SCALE3_CONST
#undef _SCALE2_CONST
#undef _SCALE1_CONST

namespace mysimulator {

  template <typename T1, typename T2>
  void scale(Array1DContent<T1>& A1, const Array1DContent<T2>& A2,
             const int& b1, const unsigned int& d1, const int& b2,
             const unsigned int& d2, const unsigned int& n) {
    assert(IsValid(A1,b1,d1,n)&&IsValid(A2,b2,d2,n));
    T1* p=A1.head+b1;
    T2* q=const_cast<T2*>(A2.head+b2);
    _scale(p,q,d1,d2,n);
  }

  template <typename T1, typename T2>
  void scale(Array1DContent<T1>& A1, const Array1DContent<T2>& A2,
             const int& b1, const int& b2, const unsigned int& n) {
    assert(IsValid(A1,b1,n)&&IsValid(A2,b2,n));
    T1* p=A1.head+b1;
    T2* q=const_cast<T2*>(A2.head+b2);
    _scale(p,q,n);
  }

  template <typename T1, typename T2>
  void scale(Array1DContent<T1>& A1, const Array1DContent<T2>& A2,
             const unsigned int& n) {
    assert(IsValid(A1,n)&&IsValid(A2,n));
    T1* p=A1.start;
    T2* q=const_cast<T2*>(A2.start);
    _scale(p,q,n);
  }

  template <typename T1, typename T2>
  void scale(Array1DContent<T1>& A1, const Array1DContent<T2>& A2) {
    assert(IsValid(A1)&&IsValid(A2));
    T1* p=A1.start;
    T2* q=const_cast<T2*>(A2.start);
    _scale(p,q,(A1.size<A2.size?A1.size:A2.size));
  }

}

#endif

