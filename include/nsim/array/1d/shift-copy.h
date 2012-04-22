
#ifndef _Array_1D_ShiftCopy_H_
#define _Array_1D_ShiftCopy_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T1,typename T2,typename T3>
  void ShiftCopy(Array1D<T1>& V,const Array1D<T2>& V2,const T3& d,
                 unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i) V[i]=V2[i]-d;
  }

  template <typename T1,typename T2,typename T3>
  void ShiftCopy(Array1D<T1>& V,const Array1D<T2>& V2,const Array1D<T3>& V3,
                 unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size())&&(n<=V3.Size()));
    for(unsigned int i=0;i<n;++i) V[i]=V2[i]+V3[i];
  }

  template <typename T1,typename T2,typename T3>
  void NegShiftCopy(Array1D<T1>& V,const Array1D<T2>& V2,const Array1D<T3>& V3,
                    unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size())&&(n<=V3.Size()));
    for(unsigned int i=0;i<n;++i) V[i]=V2[i]-V3[i];
  }

  template <typename T1,typename T2,typename T3,typename T4>
  void ShiftCopy(Array1D<T1>& V,const Array1D<T2>& V2,const Array1D<T3>& V3,
                 const T4& d,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size())&&(n<=V3.Size()));
    for(unsigned int i=0;i<n;++i) V[i]=V2[i]+d*V3[i];
  }

  template <typename T1,typename T2,typename T3,typename T4>
  void ShiftCopy(Array1D<T1>& V,const Array1D<T2>& V2,const T3& d,
                 const Array1D<T4>& V3,unsigned int n) {
    ShiftCopy(V,V2,V3,d,n);
  }

  template <typename T1,typename T2,typename T3,typename T4>
  void ShiftCopy(Array1D<T1>& V,const Array1D<T2>& V2,const Array1D<T3>& V3,
                 const Array1D<T4>& V4,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size())&&(n<=V3.Size())&&(n<=V4.Size()));
    for(unsigned int i=0;i<n;++i) V[i]=V2[i]+V3[i]*V4[i];
  }

  template <typename T1,typename T2,typename T3,typename T4,typename T5>
  void ShiftCopy(Array1D<T1>& V,const Array1D<T2>& V2,const T3& d,
                 const Array1D<T4>& V3,const Array1D<T5>& V4,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size())&&(n<=V3.Size())&&(n<=V4.Size()));
    for(unsigned int i=0;i<n;++i) V[i]=V2[i]+d*V3[i]*V4[i];
  }

}

#include "array/1d/copy.h"
#include "array/1d/shift.h"

namespace mysimulator {

  template <typename T>
  void BlasShiftCopy(Array1D<T>& V,const Array1D<T>& V2,const T& d,
                     unsigned int n) { BlasCopy(V,V2,n); BlasShift(V,d,n); }

  template <typename T>
  void BlasShiftCopy(Array1D<T>& V,const Array1D<T>& V2,const Array1D<T>& V3,
                     unsigned int n) { BlasCopy(V,V2,n); BlasShift(V,V3,n); }

  template <typename T>
  void BlasShiftCopy(Array1D<T>& V,const Array1D<T>& V2,const T& d,
                     const Array1D<T>& V3,unsigned int n) {
    BlasCopy(V,V2); BlasShift(V,d,V3,n);
  }

  template <typename T>
  void BlasShiftCopy(Array1D<T>& V,const Array1D<T>& V2,const Array1D<T>& V3,
                     const T& d,unsigned int n) {
    BlasCopy(V,V2); BlasShift(V,d,V3,n);
  }

  template <typename T>
  void BlasShiftCopy(Array1D<T>& V,const Array1D<T>& V2,const Array1D<T>& V3,
                     const Array1D<T>& V4,unsigned int n) {
    BlasCopy(V,V2); BlasShift(V,V3,V4,n);
  }

  template <typename T>
  void BlasShiftCopy(Array1D<T>& V,const Array1D<T>& V2,const T& d,
                     const Array1D<T>& V3,const Array1D<T>& V4,unsigned int n) {
    BlasCopy(V,V2); BlasShift(V,d,V3,V4,n);
  }

}

#endif

