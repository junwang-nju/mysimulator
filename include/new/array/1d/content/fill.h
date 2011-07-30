
#ifndef _Array_1D_Content_Fill_H_
#define _Array_1D_Content_Fill_H_

#include "intrinsic-type/fill.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _fill(T1* p,const T2& d,const unsigned int& n,const unsigned int& del) {
    T1* e=p+n*del;
    for(;p!=e;p+=del) fill(*p,d);
  }

  template <typename T1, typename T2>
  void _fill(T1* p, const T2& d, const unsigned int& n) {
    T1* e=p+n;
    for(;p!=e;) fill(*(p++),d);
  }

}

#include "array/reflection/single.h"
#include "linear-algebra/blas.h"
#include "intrinsic-type/constant.h"

#define _LONG_POINTER(a) reinterpret_cast<long*>(const_cast<unsigned int*>(a))

namespace mysimulator {

  template <typename T1, typename T2>
  void _fill_blas(T1* p, const T2& d, const unsigned int& n,
                  const unsigned int& del) {
    T1 td;
    copy(td,d);
    typedef typename _Single_Array<T1>::OperateType  Type;
    BLAS<Type>::Copy(
        _LONG_POINTER(&n),reinterpret_cast<Type*>(&td),
        const_cast<long*>(&lZero),reinterpret_cast<Type*>(p),
        _LONG_POINTER(&del));
  }

  template <typename T1, typename T2>
  void _fill_blas(T1* p, const T2& d, const unsigned int& n) {
    T1 td;
    copy(td,d);
    typedef typename _Single_Array<T1>::OperateType  Type;
    BLAS<Type>::Copy(
        _LONG_POINTER(&n),reinterpret_cast<Type*>(&td),
        const_cast<long*>(&lZero),reinterpret_cast<Type*>(p),
        const_cast<long*>(&lOne));
  }

}

#define _FILL_WithDel(type) \
  template <typename T>\
  void _fill(type* p,const T& d,const unsigned int& n,const unsigned int& del){\
    _fill_blas(p,d,n,del);\
  }

#define _FILL(type) \
  template <typename T>\
  void _fill(type* p,const T& d,const unsigned int& n) { _fill_blas(p,d,n); }

namespace mysimulator {

  _FILL_WithDel(double)
  _FILL_WithDel(float)
  _FILL_WithDel(long long)
  _FILL_WithDel(unsigned long long)
  _FILL_WithDel(int)
  _FILL_WithDel(unsigned int)
  _FILL_WithDel(long)
  _FILL_WithDel(unsigned long)

  _FILL(double)
  _FILL(float)
  _FILL(long long)
  _FILL(unsigned long long)
  _FILL(int)
  _FILL(unsigned int)
  _FILL(long)
  _FILL(unsigned long)

}

#undef _FILL
#undef _FILL_WithDel

#define _FLOAT_POINTER(a) reinterpret_cast<float*>(a)

namespace mysimulator {

  template <typename T>
  void _fill(long double* p,const T& d,const unsigned int& n,
             const unsigned int& del) {
    long double td;
    copy(td,d);
    long tridel=static_cast<long>(3*del);
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(&td),const_cast<long*>(&lZero),
        _FLOAT_POINTER(p),&tridel);
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(&td)+1,const_cast<long*>(&lZero),
        _FLOAT_POINTER(p)+1,&tridel);
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(&td)+2,const_cast<long*>(&lZero),
        _FLOAT_POINTER(p)+2,&tridel);
  }

  template <typename T>
  void _fill(long double* p,const T& d,const unsigned int& n) {
    long double td;
    copy(td,d);
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(&td),const_cast<long*>(&lZero),
        _FLOAT_POINTER(p),const_cast<long*>(&lThree));
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(&td)+1,const_cast<long*>(&lZero),
        _FLOAT_POINTER(p)+1,const_cast<long*>(&lThree));
    BLAS<float>::Copy(
        _LONG_POINTER(&n),_FLOAT_POINTER(&td)+2,const_cast<long*>(&lZero),
        _FLOAT_POINTER(p)+2,const_cast<long*>(&lThree));
  }

}

#undef _FLOAT_POINTER
#undef _LONG_POINTER

#include <cstring>

namespace mysimulator {

  template <typename T1, typename T2>
  void _fill_short(T1* p, const T2& d, const unsigned int& n) {
    const unsigned int m=sizeof(unsigned long long)/sizeof(T1);
    union U { unsigned long long ll; T1 s[m]; } u;
    for(unsigned int i=0;i<m;++i) fill(u.s[i],d);
    unsigned int nd=n/m, nr=n%m, ns=n-nr;
    BLAS<double>::Copy(
        reinterpret_cast<long*>(&nd),reinterpret_cast<double*>(&(u.ll)),
        const_cast<long*>(&lZero),reinterpret_cast<double*>(p),
        const_cast<long*>(&lOne));
    memcpy(p+ns,&(u.ll),nr*sizeof(T1)/sizeof(char));
  }

}

#define _FILL_SHORT(type) \
  template <typename T>\
  void _fill(type* p, const T& d, const unsigned int& n) { _fill_short(p,d,n); }

namespace mysimulator {

  _FILL_SHORT(short)
  _FILL_SHORT(unsigned short)
  _FILL_SHORT(char)
  _FILL_SHORT(unsigned char)

}

#undef _FILL_SHORT

#include "array/1d/content/interface.h"
#include "intrinsic-type/valid.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void fill(Array1DContent<T1>& A, const T2& d, const int& fst,
            const unsigned int& del, const unsigned int& n) {
    assert(IsValid(A,fst,del,n)&&IsValid(d));
    T1* p=A.head+fst;
    _fill(p,d,n,del);
  }

  template <typename T1, typename T2>
  void fill(Array1DContent<T1>& A, const T2& d, const int& fst,
            const unsigned int& n) {
    assert(IsValid(A,fst,n)&&IsValid(d));
    T1* p=A.head+fst;
    _fill(p,d,n);
  }

  template <typename T1, typename T2>
  void fill(Array1DContent<T1>& A, const T2& d, const unsigned int& n) {
    assert(IsValid(A,n)&&IsValid(d));
    T1* p=A.start;
    _fill(p,d,n);
  }

  template <typename T1, typename T2>
  void fill(Array1DContent<T1>& A, const T2& d) {
    assert(IsValid(A)&&IsValid(d));
    T1* p=A.start;
    _fill(p,d,A.size);
  }

}

#endif

