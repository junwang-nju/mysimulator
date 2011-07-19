
#ifndef _Array_1D_Shift_H_
#define _Array_1D_Shift_H_

#include "array/1d/interface.h"
#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3>
  void shift(Array1D<T1>& v, const T2& d, const Array1D<T3>& vd) {
    assert(IsValid(v)&&IsValid(vd));
    unsigned int n=(v.size<vd.size?v.size:vd.size);
    T1* p=v.start;
    T3* q=const_cast<T3*>(vd.start);
    T1* e=p+n;
    for(;p!=e;) shift(*(p++),d,*(q++));
  }

  template <typename T1, typename T2, typename T3>
  void shift(Array1D<T1>& v, const Array1D<T2>& vd, const T3& d) {
    shift(v,d,vd);
  }

  template <typename T1, typename T2>
  void shift(Array1D<T1>& v, const T2& d) {
    assert(IsValid(v));
    T1* p=v.start;
    T1* e=p+v.size;
    for(;p!=e;) shift(*(p++),d,cOne);
  }

}

#include "linear-algebra/blas.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _shift(Array1D<T1>& v, const T2& d, const Array1D<T1>& vd) {
    assert(IsValid(v)&&IsValid(vd));
    T1 td;
    copy(td,d);
    long n=(v.size<vd.size?v.size:vd.size);
    BLAS<T1>::Shift(
        &n,&td,const_cast<T1*>(vd.start),const_cast<long*>(&lOne),v.start,
        const_cast<long*>(&lOne));
  }

  template <typename T>
  void shift(Array1D<double>& v, const T& d, const Array1D<double>& vd) {
    _shift(v,d,vd);
  }

  template <typename T>
  void shift(Array1D<float>& v, const T& d, const Array1D<float>& vd) {
    _shift(v,d,vd);
  }

  template <typename T1, typename T2>
  void _shift_const(Array1D<T1>& v, const T2& d) {
    assert(IsValid(v));
    T1 td;
    copy(td,d);
    BLAS<T1>::Shift(
        reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),&td,
        const_cast<T1*>(&ValueOne<T1>()),const_cast<long*>(&lZero),v.start,
        const_cast<long*>(&lOne));
  }

  template <typename T>
  void shift(Array1D<double>& v, const T& d) { _shift_const(v,d); }

  template <typename T>
  void shift(Array1D<float>& v, const T& d) { _shift_const(v,d); }

}

#endif

