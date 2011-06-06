
#ifndef _Vector_Scale_H_
#define _Vector_Scale_H_

#include "vector/interface.h"
#include "linear-algebra/blas.h"
#include "intrinsic-type/scale.h"

namespace mysimulator {

  void scale(Vector<double>& v, const double& d) {
    assert(IsValid(v));
    dscal_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
           const_cast<double*>(&d),v(),const_cast<long*>(&lOne));
  }
  template <typename sT>
  void scale(Vector<double>& v, const sT& d) {
    double dd;
    copy(dd,d);
    scale(v,dd);
  }
  void scale(Vector<float>& v, const float& f) {
    assert(IsValid(v));
    sscal_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
           const_cast<float*>(&f),v(),const_cast<long*>(&lOne));
  }
  template <typename sT>
  void scale(Vector<float>& v, const sT& d) {
    float ff;
    copy(ff,d);
    scale(v,ff);
  }
  template <typename T, typename sT>
  void scale(Vector<T>& v, const sT& d) {
    assert(IsValid(v));
    T* p=v();
    T* pend=p+v.size;
    for(;p!=pend;)  scale(*(p++),d);
  }

  void scale(Vector<double>& v, const Vector<double>& sv) {
    assert(IsValid(v)&&IsValid(sv));
    long n=(v.size<sv.size?v.size:sv.size);
    static char flag[]="LNN";
    dtbmv_(flag,flag+1,flag+2,&n,const_cast<long*>(&lZero),
           const_cast<double*>(sv()),const_cast<long*>(&lOne),v(),
           const_cast<long*>(&lOne));
  }
  void scale(Vector<float>& v, const Vector<float>& sv) {
    assert(IsValid(v)&&IsValid(sv));
    long n=(v.size<sv.size?v.size:sv.size);
    static char flag[]="LNN";
    stbmv_(flag,flag+1,flag+2,&n,const_cast<long*>(&lZero),
           const_cast<float*>(sv()),const_cast<long*>(&lOne),v(),
           const_cast<long*>(&lOne));
  }
  template <typename T, typename sT>
  void scale(Vector<T>& v, const Vector<sT>& sv) {
    assert(IsValid(v)&&IsValid(sv));
    unsigned int n=(v.size<sv.size?v.size:sv.size);
    T* p=v();
    sT* sp=const_cast<sT*>(sv());
    T* pend=p+n;
    for(;p!=pend;)  scale(*(p++),*(sp++));
  }

  template <typename T, typename sT1, typename sT2>
  void scale(Vector<T>& v, const Vector<sT1>& sv, const sT2& d) {
    scale(v,sv);
    scale(v,d);
  }
  template <typename T, typename sT1, typename sT2>
  void scale(Vector<T>& v, const sT1& d, const Vector<sT2>& sv) {
    scale(v,d);
    scale(v,sv);
  }

}

#endif

