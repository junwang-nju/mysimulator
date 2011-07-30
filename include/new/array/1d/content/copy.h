
#ifndef _Array_1D_Content_Copy_H_
#define _Array_1D_Content_Copy_H_

#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _copy(T1* p, T2* q, const unsigned int& n,
                     const unsigned int& del, const unsigned int& cdel) {
    T1* e=p+n*del;
    for(;p!=e;p+=del,q+=cdel) copy(*p,*q);
  }

  template <typename T1, typename T2>
  void _copy(T1* p, T2* q, const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;) copy(*(p++),*(q++));
  }

}

#include "linear-algebra/blas.h"
#include "intrinsic-type/constant.h"
#include "array/reflection/single.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T>
  void _copy_blas(T* p, T* q, const unsigned int& n, const unsigned int& del,
                  const unsigned int& cdel) {
    typedef typename _Single_Array<T>::OperateType    Type;
    BLAS<Type>::Copy(
        _LONG_POINTER(&n),reinterpret_cast<Type*>(q),
        _LONG_POINTER(&cdel),reinterpret_cast<Type*>(p),_LONG_POINTER(&del));
  }

  template <typename T>
  void _copy_blas(T* p, T* q, const unsigned int& n) {
    typedef typename _Single_Array<T>::OperateType    Type;
    BLAS<Type>::Copy(
        _LONG_POINTER(&n),reinterpret_cast<Type*>(q),const_cast<long*>(&lOne),
        reinterpret_cast<Type*>(p),const_cast<long*>(&lOne));
  }

}

#define _COPY_WithDel(type) \
  void _copy(type* p, type* q, const unsigned int& n, const unsigned int& del,\
             const unsigned int& cdel) { _copy_blas(p,q,n,del,cdel); }

#define _COPY(type) \
  void _copy(type* p, type* q, const unsigned int& n) {\
    _copy_blas(p,q,n);\
  }

namespace mysimulator {

  _COPY_WithDel(double)
  _COPY_WithDel(float)
  _COPY_WithDel(long long)
  _COPY_WithDel(unsigned long long)
  _COPY_WithDel(int)
  _COPY_WithDel(unsigned int)
  _COPY_WithDel(long)
  _COPY_WithDel(unsigned long)

  _COPY(double)
  _COPY(float)
  _COPY(long long)
  _COPY(unsigned long long)
  _COPY(int)
  _COPY(unsigned int)
  _COPY(long)
  _COPY(unsigned long)

}

#undef _COPY
#undef _COPY_WithDel

#define _FLOAT_POINTER(a) reinterpret_cast<float*>(a)

namespace mysimulator {

  void _copy(long double* p, long double* q, const unsigned int& n,
             const unsigned int& del, const unsigned int& cdel) {
    long d=static_cast<long>(del+del+del);
    long cd=static_cast<long>(cdel+cdel+cdel);
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(q),&cd,_FLOAT_POINTER(p),&d);
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(q)+1,&cd,_FLOAT_POINTER(p)+1,&d);
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(q)+2,&cd,_FLOAT_POINTER(p)+2,&d);
  }

  void _copy(long double* p, long double* q, const unsigned int& n) {
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(q),const_cast<long*>(&lThree),
        _FLOAT_POINTER(p),const_cast<long*>(&lThree));
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(q)+1,const_cast<long*>(&lThree),
        _FLOAT_POINTER(p)+1,const_cast<long*>(&lThree));
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(q)+2,const_cast<long*>(&lThree),
        _FLOAT_POINTER(p)+2,const_cast<long*>(&lThree));
  }

}

#undef _FLOAT_POINTER
#undef _LONG_POINTER

#include <cstring>

#define _COPY_SHORT(type) \
  void _copy(type* p, type* q, const unsigned int& n) {\
    memcpy(p,q,n*sizeof(type));\
  }

namespace mysimulator {

  _COPY_SHORT(short)
  _COPY_SHORT(unsigned short)
  _COPY_SHORT(char)
  _COPY_SHORT(unsigned char)

}

#undef _COPY_SHORT

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void copy(Array1DContent<T1>& v, const Array1DContent<T2>& cv,
            const int& fst, const unsigned int& del, const int& cfst,
            const unsigned int& cdel, const unsigned int& n) {
    assert(IsValid(v,fst,del,n)&&IsValid(cv,cfst,cdel,n));
    T1* p=v.head+fst;
    T2* q=const_cast<T2*>(cv.head)+cfst;
    _copy(p,q,n,del,cdel);
  }

  template <typename T1, typename T2>
  void copy(Array1DContent<T1>& v, const Array1DContent<T2>& cv,
            const int& fst, const int& cfst, const unsigned int& n) {
    assert(IsValid(v,fst,n)&&IsValid(cv,cfst,n));
    T1* p=v.head+fst;
    T2* q=const_cast<T2*>(cv.head)+cfst;
    _copy(p,q,n);
  }

  template <typename T1, typename T2>
  void copy(Array1DContent<T1>& v, const Array1DContent<T2>& cv,
            const unsigned int& n) {
    assert(IsValid(v,n)&&IsValid(cv,n));
    T1* p=v.start;
    T2* q=const_cast<T2*>(cv.start);
    _copy(p,q,n);
  }

  template <typename T1, typename T2>
  void copy(Array1DContent<T1>& v, const Array1DContent<T2>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    T1* p=v.start;
    T2* q=const_cast<T2*>(cv.start);
    _copy(p,q,(v.size<cv.size?v.size:cv.size));
  }

}

#endif

