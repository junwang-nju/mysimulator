
#ifndef _Array_2D_Exchange_H_
#define _Array_2D_Exchange_H_

#include "array/1d/interface.h"
#include "intrinsic-type/exchange.h"

namespace mysimulator {

  template <typename T>
  void exchange(Array1D<T>& va, Array1D<T>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    T* pa=va.start;
    T* pb=vb.start;
    T* pe=pa+n;
    for(;pa!=pe;) exchange(*(pa++),*(pb++));
  }

}

#include "linear-algebra/blas.h"
#include "array/reflection/single.h"

namespace mysimulator {

  template <typename T>
  void _exchange(Array1D<T>& va, Array1D<T>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    typedef typename _Single_Array<T>::OperateType  Type;
    long n=(va.size<vb.size?va.size:vb.size);
    BLAS<Type>::Swap(
        &n,reinterpret_cast<Type*>(va.start),const_cast<long*>(&lOne),
           reinterpret_cast<Type*>(vb.start),const_cast<long*>(&lOne));
  }

  void exchange(Array1D<double>& va, Array1D<double>& vb) { _exchange(va,vb); }
  void exchange(Array1D<float>& va, Array1D<float>& vb) { _exchange(va,vb); }
  void exchange(Array1D<long long>& va, Array1D<long long>& vb) {
    _exchange(va,vb);
  }
  void exchange(Array1D<unsigned long long>& va,
                Array1D<unsigned long long>& vb) { _exchange(va,vb); }
  void exchange(Array1D<long>& va, Array1D<long>& vb) { _exchange(va,vb); }
  void exchange(Array1D<unsigned long>& va, Array1D<unsigned long>& vb) {
    _exchange(va,vb);
  }
  void exchange(Array1D<int>& va, Array1D<int>& vb) { _exchange(va,vb); }
  void exchange(Array1D<unsigned int>& va, Array1D<unsigned int>& vb) {
    _exchange(va,vb);
  }

  void exchange(Array1D<long double>& va, Array1D<long double>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    n=n+n+n;
    sswap_(
        &n,reinterpret_cast<float*>(va.start),const_cast<long*>(&lOne),
           reinterpret_cast<float*>(vb.start),const_cast<long*>(&lOne));
  }

  void exchange(Array1D<short>& va, Array1D<short>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    long ni=(n>>1), nr=(n&1), nb=n-nr;
    sswap_(&ni,reinterpret_cast<float*>(va.start),const_cast<long*>(&lOne),
               reinterpret_cast<float*>(vb.start),const_cast<long*>(&lOne));
    if(nr!=0) exchange(va[nb],vb[nb]);
  }

  void exchange(Array1D<unsigned short>& va, Array1D<unsigned short>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    long ni=(n>>1), nr=(n&1);
    sswap_(&ni,reinterpret_cast<float*>(va.start),const_cast<long*>(&lOne),
               reinterpret_cast<float*>(vb.start),const_cast<long*>(&lOne));
    if(nr!=0) exchange(va[va.last],vb[vb.last]);
  }

  void exchange(Array1D<char>& va, Array1D<char>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    long ni=(n>>2);
    unsigned int nr=(n&3);
    sswap_(&ni,reinterpret_cast<float*>(va.start),const_cast<long*>(&lOne),
               reinterpret_cast<float*>(vb.start),const_cast<long*>(&lOne));
    for(unsigned int i=0;i<nr;++i)
      exchange(va[va.last-i],vb[vb.last-i]);
  }

  void exchange(Array1D<unsigned char>& va, Array1D<unsigned char>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    long ni=(n>>2);
    unsigned int nr=(n&3);
    sswap_(&ni,reinterpret_cast<float*>(va.start),const_cast<long*>(&lOne),
               reinterpret_cast<float*>(vb.start),const_cast<long*>(&lOne));
    for(unsigned int i=0;i<nr;++i)
      exchange(va[va.last-i],vb[vb.last-i]);
  }

}

#endif

