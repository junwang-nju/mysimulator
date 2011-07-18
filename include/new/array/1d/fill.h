
#ifndef _Array_1D_Fill_H_
#define _Array_1D_Fill_H_

#include "array/1d/interface.h"
#include "intrinsic-type/valid.h"

namespace mysimulator {

  template <typename T, typename cT>
  void fill(Array1D<T>& v, const cT& d) {
    assert(IsValid(v)&&IsValid(d));
    T* p=v.start;
    T* e=v.start+v.size;
    for(;p!=e;) fill(*(p++),d);
  }

}

#include "intrinsic-type/fill.h"
#include "array/reflection/single.h"
#include "linear-algebra/blas.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T, typename cT>
  void _fill(Array1D<T>& v, const cT& d) {
    assert(IsValid(v));
    T td;
    fill(td,d);
    typedef typename _Single_Array<T>::OperateType Type;
    BLAS<Type>::Copy(
        reinterpret_cast<long*>(&(v.size)),reinterpret_cast<Type*>(&td),
        const_cast<long*>(&lZero),reinterpret_cast<Type*>(v.start),
        const_cast<long*>(&lOne));
  }

  template <typename T>
  void fill(Array1D<double>& v, const T& d) { _fill(v,d); }

  template <typename T>
  void fill(Array1D<float>& v, const T& d) { _fill(v,d); }

  template <typename T>
  void fill(Array1D<long long>& v, const T& d) { _fill(v,d); }

  template <typename T>
  void fill(Array1D<unsigned long long>& v, const T& d) { _fill(v,d); }

  template <typename T>
  void fill(Array1D<int>& v, const T& d) { _fill(v,d); }

  template <typename T>
  void fill(Array1D<unsigned int>& v, const T& d) { _fill(v,d); }

  template <typename T>
  void fill(Array1D<long double>& v, const T& d) {
    assert(IsValid(v));
    long double td;
    fill(td,d);
    BLAS<float>::Copy(
        reinterpret_cast<long*>(&(v.size)),reinterpret_cast<float*>(&td),
        const_cast<long*>(&lZero),reinterpret_cast<float*>(v.start),
        const_cast<long*>(&lThree));
    BLAS<float>::Copy(
        reinterpret_cast<long*>(&(v.size)),reinterpret_cast<float*>(&td)+1,
        const_cast<long*>(&lZero),reinterpret_cast<float*>(v.start)+1,
        const_cast<long*>(&lThree));
    BLAS<float>::Copy(
        reinterpret_cast<long*>(&(v.size)),reinterpret_cast<float*>(&td)+2,
        const_cast<long*>(&lZero),reinterpret_cast<float*>(v.start)+2,
        const_cast<long*>(&lThree));
  }

}

#include <cstring>

namespace mysimulator {

  template <typename T, typename cT>
  void _fill_short(Array1D<T>& v, const cT& d) {
    assert(IsValid(v));
    const unsigned int n=sizeof(unsigned long long)/sizeof(T);
    union U { unsigned long long ll; T s[n]; } u;
    for(unsigned int i=0;i<n;++i) fill(u.s[i],d);
    unsigned int nd=v.size/n,nr=v.size%n,ns=v.size-nr;
    BLAS<double>::Copy(
        reinterpret_cast<long*>(&nd),reinterpret_cast<double*>(&(u.ll)),
        const_cast<long*>(&lZero),reinterpret_cast<double*>(v.start),
        const_cast<long*>(&lOne));
    memcpy(reinterpret_cast<char*>(v.start+ns),&(u.ll),
           nr*sizeof(T)/sizeof(char));
  }

  template <typename T>
  void fill(Array1D<short>& v, const T& s) { _fill_short(v,s); }

  template <typename T>
  void fill(Array1D<unsigned short>& v, const T& s) { _fill_short(v,s); }

  template <typename T>
  void fill(Array1D<char>& v, const T& s) { _fill_short(v,s); }

  template <typename T>
  void fill(Array1D<unsigned char>& v, const T& s) { _fill_short(v,s); }

}

#endif

