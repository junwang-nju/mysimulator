
#ifndef _Array_1D_Shift_H_
#define _Array_1D_Shift_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void Shift(Array1D<T1>& V,const T2& d,unsigned int n) {
    assert(n<=V.Size());
    for(unsigned int i=0;i<n;++i) V[i]+=d;
  }

  template <typename T1,typename T2>
  void Shift(Array1D<T1>& V,const Array1D<T2>& V2,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i) V[i]+=V2[i];
  }

  template <typename T1,typename T2>
  void NegShift(Array1D<T1>& V,const Array1D<T2>& V2,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i) V[i]-=V2[i];
  }

  template <typename T1,typename T2, typename T3>
  void Shift(Array1D<T1>& V,const Array1D<T2>& V2,const T3& d,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i) V[i]+=V2[i]*d;
  }

  template <typename T1,typename T2, typename T3>
  void Shift(Array1D<T1>& V,const T2& d,const Array1D<T3>& V2,unsigned int n) {
    Shift(V,V2,d,n);
  }

  template <typename T1,typename T2, typename T3>
  void Shift(Array1D<T1>& V,const Array1D<T2>& V2,const Array1D<T3>& V3,
             unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size())&&(n<=V3.Size()));
    for(unsigned int i=0;i<n;++i) V[i]+=V2[i]*V3[i];
  }

  template <typename T1,typename T2, typename T3,typename T4>
  void Shift(Array1D<T1>& V,const T2& d,const Array1D<T3>& V3,
             const Array1D<T3>& V4,unsigned int n) {
    assert((n<=V.Size())&&(n<=V3.Size())&&(n<=V4.Size()));
    for(unsigned int i=0;i<n;++i) V[i]+=d*V3[i]*V4[i];
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void BlasShift(Array1D<double>& V,const double& d,unsigned int n) {
    assert(n<=V.Size());
    long m=n, one=1, zero=0;
    double done=1.;
    BLAS<double>::Shift(&m,&done,const_cast<double*>(&d),&zero,V._data,&one);
  }
  void BlasShift(Array1D<float>& V,const float& d,unsigned int n) {
    assert(n<=V.Size());
    long m=n, one=1, zero=0;
    float fone=1.;
    BLAS<float>::Shift(&m,&fone,const_cast<float*>(&d),&zero,V._data,&one);
  }

  void BlasShift(Array1D<double>& V,const double& d,const Array1D<double>& V2,
                 unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    long m=n, one=1;
    BLAS<double>::Shift(&m,const_cast<double*>(&d),
                        const_cast<double*>(V2._data),&one,V._data,&one);
  }
  void BlasShift(Array1D<float>& V,const float& d,const Array1D<float>& V2,
                 unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    long m=n, one=1;
    BLAS<float>::Shift(&m,const_cast<float*>(&d),
                       const_cast<float*>(V2._data),&one,V._data,&one);
  }

  void BlasShift(Array1D<double>& V,const Array1D<double>& V2,unsigned int n) {
    BlasShift(V,1.,V2,n);
  }
  void BlasShift(Array1D<float>& V,const Array1D<float>& V2,unsigned int n) {
    BlasShift(V,1.,V2,n);
  }

  void BlasShift(Array1D<double>& V,const Array1D<double>& V2,const double& d,
                 unsigned int n) { BlasShift(V,d,V2,n); }
  void BlasShift(Array1D<float>& V,const Array1D<float>& V2,const float& d,
                 unsigned int n) { BlasShift(V,d,V2,n); }

  void BlasShift(Array1D<double>& V,const double& d,const Array1D<double>& V3,
                 const Array1D<double>& V4,unsigned int n) {
    assert((n<=V.Size())&&(n<=V3.Size())&&(n<=V4.Size()));
    long m=n, one=1, zero=0;
    double done=1.;
    static char FG[]="L";
    BLAS<double>::SbMv(FG,&m,&zero,const_cast<double*>(&d),
                       const_cast<double*>(V3._data),&one,
                       const_cast<double*>(V4._data),&one,&done,V._data,&one);
  }
  void BlasShift(Array1D<float>& V,const float& d,const Array1D<float>& V3,
                 const Array1D<float>& V4,unsigned int n) {
    assert((n<=V.Size())&&(n<=V3.Size())&&(n<=V4.Size()));
    long m=n, one=1, zero=0;
    float fone=1.;
    static char FG[]="L";
    BLAS<float>::SbMv(FG,&m,&zero,const_cast<float*>(&d),
                      const_cast<float*>(V3._data),&one,
                      const_cast<float*>(V4._data),&one,&fone,V._data,&one);
  }

  void BlasShift(Array1D<double>& V,const Array1D<double>& V2,
                 const Array1D<double>& V3,unsigned int n) {
    BlasShift(V,1.,V2,V3,n);
  }
  void BlasShift(Array1D<float>& V,const Array1D<float>& V2,
                 const Array1D<float>& V3,unsigned int n) {
    BlasShift(V,1.,V2,V3,n);
  }

}

#endif

