
#ifndef _Array_1D_Content_Exchange_H_
#define _Array_1D_Content_Exchange_H_

#include "intrinsic-type/exchange.h"

namespace mysimulator {

  template <typename T>
  void _exchange(T* p,T* q,const unsigned int& d1,const unsigned int& d2,
                 const unsigned int& n) {
    T* e=p+d1*n;
    for(;p!=e;p+=d1,q+=d2)  exchange(*p,*q);
  }

  template <typename T>
  void _exchange(T* p,T* q,const unsigned int& n) {
    T* e=p+n;
    for(;p!=e;) exchange(*(p++),*(q++));
  }

}

#include "linear-algebra/blas.h"
#include "array/reflection/single.h"
#include "intrinsic-type/constant.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T>
  void _exchange_blas(T* p,T* q,const unsigned int& d1,const unsigned int& d2,
                      const unsigned int& n) {
    typedef typename _Single_Array<T>::OperateType    Type;
    BLAS<Type>::Swap(
        _LONG_POINTER(&n),reinterpret_cast<Type*>(q),_LONG_POINTER(&d1),
        reinterpret_cast<Type*>(p),_LONG_POINTER(&d2));
  }

  template <typename T>
  void _exchange_blas(T* p,T* q,const unsigned int& n) {
    typedef typename _Single_Array<T>::OperateType    Type;
    BLAS<Type>::Swap(
        _LONG_POINTER(&n),reinterpret_cast<Type*>(q),const_cast<long*>(&lOne),
        reinterpret_cast<Type*>(p),const_cast<long*>(&lOne));
  }

}

#define _EXCHANGE_WithDel(type) \
  void _exchange(type* p, type* q, const unsigned int& d1,\
                 const unsigned int& d2, const unsigned int& n) {\
    _exchange_blas(p,q,d1,d2,n);\
  }

#define _EXCHANGE(type) \
  void _exchange(type* p, type* q, const unsigned int& n) {\
    _exchange_blas(p,q,n);\
  }

#define _EXCHANGE_DATA(type) \
  _EXCHANGE_WithDel(type)\
  _EXCHANGE(type)

namespace mysimulator {

  _EXCHANGE_DATA(double)
  _EXCHANGE_DATA(float)
  _EXCHANGE_DATA(long long)
  _EXCHANGE_DATA(unsigned long long)
  _EXCHANGE_DATA(int)
  _EXCHANGE_DATA(unsigned int)
  _EXCHANGE_DATA(long)
  _EXCHANGE_DATA(unsigned long)

}

#undef _EXCHANGE_DATA
#undef _EXCHANGE
#undef _EXCHANGE_WithDel

#define _FLOAT_POINTER(a) reinterpret_cast<float*>(a)

namespace mysimulator {

  void _exchange(long double* p, long double* q, const unsigned int& d1,
                 const unsigned int& d2, const unsigned int& n) {
    long D1=static_cast<long>(d1+d1+d1);
    long D2=static_cast<long>(d2+d2+d2);
    BLAS<float>::Swap(
        _LONG_POINTER(&n),_FLOAT_POINTER(q),&D1,_FLOAT_POINTER(p),&D2);
    BLAS<float>::Swap(
        _LONG_POINTER(&n),_FLOAT_POINTER(q)+1,&D1,_FLOAT_POINTER(p)+1,&D2);
    BLAS<float>::Swap(
        _LONG_POINTER(&n),_FLOAT_POINTER(q)+2,&D1,_FLOAT_POINTER(p)+2,&D2);
  }

  void _exchange(long double* p, long double* q, const unsigned int& n) {
    BLAS<float>::Swap(
        _LONG_POINTER(&n),_FLOAT_POINTER(q),const_cast<long*>(&lThree),
        _FLOAT_POINTER(p),const_cast<long*>(&lThree));
    BLAS<float>::Swap(
        _LONG_POINTER(&n),_FLOAT_POINTER(q)+1,const_cast<long*>(&lThree),
        _FLOAT_POINTER(p)+1,const_cast<long*>(&lThree));
    BLAS<float>::Swap(
        _LONG_POINTER(&n),_FLOAT_POINTER(q)+2,const_cast<long*>(&lThree),
        _FLOAT_POINTER(p)+2,const_cast<long*>(&lThree));
  }

}

#undef _FLOAT_POINTER
#undef _LONG_POINTER

namespace mysimulator {

  template <typename T>
  void _exchange_short(T* p,T* q,const unsigned int& n) {
    long m=sizeof(unsigned long long)/sizeof(T);
    long nl=n/m, nr=n%m, nb=n-nr;
    typedef typename _Single_Array<unsigned long long>::OperateType    Type;
    BLAS<Type>::Swap(
        &nl,reinterpret_cast<Type*>(q),const_cast<long*>(&lOne),
        reinterpret_cast<Type*>(p),const_cast<long*>(&lOne));
    p+=nb;
    q+=nb;
    T* e=p+nr;
    for(;p!=e;) exchange(*(p++),*(q++));
  }

}

#define _EXCHANGE_SHORT(type) \
  void _exchange(type* p, type* q, const unsigned int& n) {\
    _exchange_short(p,q,n);\
  }

namespace mysimulator {

  _EXCHANGE_SHORT(short)
  _EXCHANGE_SHORT(unsigned short)
  _EXCHANGE_SHORT(char)
  _EXCHANGE_SHORT(unsigned char)

}

#undef _EXCHANGE_SHORT

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void exchange(Array1DContent<T>& A1, Array1DContent<T>& A2, const int& b1,
                const unsigned int& d1, const int& b2, const unsigned int& d2,
                const unsigned int& n) {
    assert(IsValid(A1,b1,d1,n)&&IsValid(A2,b2,d2,n));
    T* p=A1.head+b1;
    T* q=A2.head+b2;
    _exchange(p,q,d1,d2,n);
  }

  template <typename T>
  void exchange(Array1DContent<T>& A1, Array1DContent<T>& A2, const int& b1,
                const int& b2, const unsigned int& n) {
    assert(IsValid(A1,b1,n)&&IsValid(A2,b2,n));
    T* p=A1.head+b1;
    T* q=A2.head+b2;
    _exchange(p,q,n);
  }

  template <typename T>
  void exchange(Array1DContent<T>& A1, Array1DContent<T>& A2,
                const unsigned int& n) {
    assert(IsValid(A1,n)&&IsValid(A2,n));
    T* p=A1.start;
    T* q=A2.start;
    _exchange(p,q,n);
  }

  template <typename T>
  void exchange(Array1DContent<T>& A1, Array1DContent<T>& A2) {
    assert(IsValid(A1)&&IsValid(A2));
    T* p=A1.start;
    T* q=A2.start;
    _exchange(p,q,(A1.size<A2.size?A1.size:A2.size));
  }

}

#endif

