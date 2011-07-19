
#ifndef _Array_1D_Scale_H_
#define _Array_1D_Scale_H_

#include "array/1d/interface.h"
#include "intrinsic-type/scale.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void scale(Array1D<T1>& v, const T2& d) {
    assert(IsValid(v));
    T1* p=v.start;
    T1* e=p+v.size;
    for(;p!=e;) scale(*(p++),d);
  }

  template <typename T1, typename T2>
  void scale(Array1D<T1>& v, const Array1D<T2>& vd) {
    assert(IsValid(v)&&IsValid(vd));
    unsigned int n=(v.size<vd.size?v.size:vd.size);
    T1* p=v.start;
    T2* q=const_cast<T2*>(vd.start);
    T1* e=p+n;
    for(;p!=e;) scale(*(p++),*(q++));
  }

}

#include "linear-algebra/blas.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _scale(Array1D<T1>& v, const T2& d) {
    assert(IsValid(v));
    T1 rd;  // think T1 is a simple type
    copy(rd,d);
    BLAS<T1>::Scale(
        reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
        const_cast<T1*>(&rd),v.start,const_cast<long*>(&lOne));
  }

  template <typename T>
  void scale(Array1D<double>& v, const T& d) { _scale(v,d); }

  template <typename T>
  void scale(Array1D<float>& v, const T& d) { _scale(v,d); }

  template <typename T>
  void _scale_array(Array1D<T>& v, const Array1D<T>& vd) {
    assert(IsValid(v)&&IsValid(vd));
    long n=(v.size<vd.size?v.size:vd.size);
    static char flag[]="LNN";
    BLAS<T>::TbMv(
        flag,flag+1,flag+2,&n,const_cast<long*>(&lZero),
        const_cast<T*>(vd.start),const_cast<long*>(&lOne),v.start,
        const_cast<long*>(&lOne));
  }

  void scale(Array1D<double>& v,const Array1D<double>& vd) {_scale_array(v,vd);}

  void scale(Array1D<float>& v,const Array1D<float>& vd) { _scale_array(v,vd); }

  template <typename T1, typename T2, typename T3>
  void scale(Array1D<T1>& v, const Array1D<T2>& vd, const T3& d) {
    scale(v,vd);
    scale(v,d);
  }

  template <typename T1, typename T2, typename T3>
  void scale(Array1D<T1>& v, const T2& d, const Array1D<T3>& vd) {
    scale(v,vd,d);
  }

}

#endif

