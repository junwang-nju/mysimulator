
#ifndef _Vector_Shift_H_
#define _Vector_Shift_H_

#include "vector/interface.h"
#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename T, typename fT, typename sT>
  void shift(Vector<T>& v, const fT& d, const Vector<sT>& sv) {
    assert(IsValid(v)&&IsValid(sv));
    unsigned int n=(v.size<sv.size?v.size:sv.size);
    T* p=v();
    sT* sp=const_cast<sT*>(sv());
    T* pend=p+n;
    for(;p!=pend;)  shift(*(p++),d,*(sp++));
  }

  template <typename T, typename fT, typename sT>
  void shift(Vector<T>& v, const Vector<sT>& sv, const fT& d) { shift(v,d,sv); }

  void shift(Vector<double>& v, const double& d, const Vector<double>& sv) {
    assert(IsValid(v)&&IsValid(sv));
    long n=(v.size<sv.size?v.size:sv.size);
    daxpy_(&n,const_cast<double*>(&d),const_cast<double*>(sv()),
           const_cast<long*>(&lOne),v(),const_cast<long*>(&lOne));
  }

  void shift(Vector<float>& v, const float& d, const Vector<float>& sv) {
    assert(IsValid(v)&&IsValid(sv));
    long n=(v.size<sv.size?v.size:sv.size);
    saxpy_(&n,const_cast<float*>(&d),const_cast<float*>(sv()),
           const_cast<long*>(&lOne),v(),const_cast<long*>(&lOne));
  }

  template <typename T>
  void shift(Vector<double>& v, const T& d, const Vector<double>& sv) {
    double dd;
    copy(dd,d);
    shift(v,dd,sv);
  }

  template <typename T>
  void shift(Vector<float>& v, const T& d, const Vector<float>& sv) {
    float dd;
    copy(dd,d);
    shift(v,dd,sv);
  }

  template <typename T, typename fT>
  void shift(Vector<T>& v, const fT& d) {
    assert(IsValid(v));
    T* p=v();
    T* pend=p+v.size;
    for(;p!=pend;)  shift(*(p++),d,static_cast<T>(cOne));
  }

  void shift(Vector<double>& v, const double& d) {
    assert(IsValid(v));
    daxpy_(reinterpret_cast<long*>(&(v.size)),const_cast<double*>(&d),
           const_cast<double*>(&dOne),const_cast<long*>(&lZero),v(),
           const_cast<long*>(&lOne));
  }

  void shift(Vector<float>& v, const float& d) {
    assert(IsValid(v));
    saxpy_(reinterpret_cast<long*>(&(v.size)),const_cast<float*>(&d),
           const_cast<float*>(&fOne),const_cast<long*>(&lZero),v(),
           const_cast<long*>(&lOne));
  }

  template <typename T>
  void shift(Vector<double>& v, const T& d) {
    double dd;
    copy(dd,d);
    shift(v,dd);
  }

  template <typename T>
  void shift(Vector<float>& v, const T& d) {
    float dd;
    copy(dd,d);
    shift(v,dd);
  }

  template <typename T, typename sT>
  void shift(Vector<T>& v, const Vector<sT>& sv) {
    shift(v,static_cast<T>(cOne),sv);
  }

}

#include "vector/scale.h"

namespace mysimulator {

  template <typename T,typename dT,typename cT,typename fT,typename sT>
  void scaleshift(Vector<T>& v, const dT& d, const cT& cd,
                  const Vector<fT>& fv, const Vector<sT>& sv) {
    assert(IsValid(v)&&IsValid(fv)&&IsValid(sv));
    unsigned int n;
    n=(v.size<fv.size?v.size:fv.size);
    n=(n<sv.size?n:sv.size);
    T* p=v();
    fT* fp=const_cast<fT*>(fv());
    sT* sp=const_cast<sT*>(sv());
    T* pend=p+n;
    for(;p!=pend;)  {
      scale(*p,d);
      shift(*(p++),cd*(*(fp++)),*(sp++));
    }
  }

  void scaleshift(Vector<double>& v, const double& d, const double& cd,
                  const Vector<double>& fv, const Vector<double>& sv) {
    assert(IsValid(v)&&IsValid(fv)&&IsValid(sv));
    long n;
    n=static_cast<long>(v.size<fv.size?v.size:fv.size);
    n=(static_cast<unsigned int>(n)<sv.size?n:static_cast<long>(sv.size));
    static char flag[]="L";
    dsbmv_(flag,&n,const_cast<long*>(&lZero),const_cast<double*>(&cd),
           const_cast<double*>(fv()),const_cast<long*>(&lOne),
           const_cast<double*>(sv()),const_cast<long*>(&lOne),
           const_cast<double*>(&d),v(),const_cast<long*>(&lOne));
  }

  void scaleshift(Vector<float>& v, const float& d, const float& cd,
                  const Vector<float>& fv, const Vector<float>& sv) {
    assert(IsValid(v)&&IsValid(fv)&&IsValid(sv));
    long n;
    n=static_cast<long>(v.size<fv.size?v.size:fv.size);
    n=(static_cast<unsigned int>(n)<sv.size?n:static_cast<long>(sv.size));
    static char flag[]="L";
    ssbmv_(flag,&n,const_cast<long*>(&lZero),const_cast<float*>(&cd),
           const_cast<float*>(fv()),const_cast<long*>(&lOne),
           const_cast<float*>(sv()),const_cast<long*>(&lOne),
           const_cast<float*>(&d),v(),const_cast<long*>(&lOne));
  }

  template <typename dT, typename cT>
  void scaleshift(Vector<double>& v, const dT& d, const cT& cd,
                  const Vector<double>& fv, const Vector<double>& sv) {
    double dd,dcd;
    copy(dd,d);
    copy(dcd,cd);
    scaleshift(v,dd,dcd,fv,sv);
  }

  template <typename dT, typename cT>
  void scaleshift(Vector<float>& v, const dT& d, const cT& cd,
                  const Vector<float>& fv, const Vector<float>& sv) {
    float dd,dcd;
    copy(dd,d);
    copy(dcd,cd);
    scaleshift(v,dd,dcd,fv,sv);
  }

  template <typename T,typename dT,typename fT,typename sT>
  void scaleshift(Vector<T>& v, const dT& d, const Vector<fT>& fv,
                  const Vector<sT>& sv) {
    scaleshift(v,d,static_cast<T>(cOne),fv,sv);
  }

  template <typename T,typename dT,typename cT,typename sT>
  void scaleshift(Vector<T>& v,const dT& d,const cT& cd,const Vector<sT>& sv) {
    scale(v,d);
    shift(v,cd,sv);
  }

  template <typename T,typename cT,typename fT,typename sT>
  void shift(Vector<T>& v, const cT& cd, const Vector<fT>& fv,
             const Vector<sT>& sv) {
    scaleshift(v,static_cast<T>(cOne),cd,fv,sv);
  }

}

#endif

