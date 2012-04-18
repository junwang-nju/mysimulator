
#ifndef _Array_1D_Shift_H_
#define _Array_1D_Shift_H_

namespace mysimulator {

  template <typename T1, typename T2>
  void Shift(T1* p, const T2& d, unsigned int n) {
    for(unsigned int i=0;i<n;++i) p[i]+=d;
  }

  template <typename T1, typename T2>
  void Shift(T1* p, const T2* q, unsigned int n) {
    for(unsigned int i=0;i<n;++i) p[i]+=q[i];
  }

  template <typename T1, typename T2, typename T3>
  void Shift(T1* p, const T2& d, const T3* q, unsigned int n) {
    for(unsigned int i=0;i<n;++i) p[i]+=d*q[i];
  }

  template <typename T1, typename T2, typename T3>
  void Shift(T1* p, const T2* q, const T3& d, unsigned int n) { Shift(p,d,q); }

  template <typename T1, typename T2, typename T3>
  void Shift(T1* p, const T2* q1, const T2* q2, unsigned int n) {
    for(unsigned int i=0;i<n;++i) p[i]+=q1[i]*q2[i];
  }

  template <typename T1, typename T2, typename T3, typename T4>
  void Shift(T1* p, const T2& d, const T3* q1, const T4* q2, unsigned int n) {
    for(unsigned int i=0;i<n;++i) p[i]+=d*q1[i]*q2[i];
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void BLASShift(double* p, const double& d, unsigned int n) {
    long m=n, one=1, zero=0;
    double done=1.;
    BLAS<double>::Shift(&m,&done,const_cast<double*>(&d),&zero,p,&one);
  }

  void BLASShift(float* p, const float& d, unsigned int n) {
    long m=n, one=1, zero=0;
    float fone=1.;
    BLAS<float>::Shift(&m,&fone,const_cast<float*>(&d),&zero,p,&one);
  }

  void BLASShift(double* p, const double* q, unsigned int n) {
    long m=n, one=1;
    double done=1.;
    BLAS<double>::Shift(&m,&done,const_cast<double*>(q),&one,p,&one);
  }

  void BLASShift(float* p, const float* q, unsigned int n) {
    long m=n, one=1;
    float fone=1.;
    BLAS<float>::Shift(&m,&fone,const_cast<float*>(q),&one,p,&one);
  }

  void BLASShift(double* p, const double& d, const double* q, unsigned int n) {
    long m=n, one=1;
    BLAS<double>::Shift(&m,const_cast<double*>(&d),
                        const_cast<double*>(q),&one,p,&one);
  }

  void BLASShift(float* p, const float& d, const float* q, unsigned int n) {
    long m=n, one=1;
    BLAS<float>::Shift(&m,const_cast<float*>(&d),
                       const_cast<float*>(q),&one,p,&one);
  }

  void BLASShift(double* p, const double* q1, const double* q2, unsigned int n){
    long m=n, one=1, zero=0;
    double done=1.;
    static char FG[]="L";
    BLAS<double>::SbMv(FG,&m,&zero,&done,const_cast<double*>(q1),&one,
                       const_cast<double*>(q2),&one,&done,p,&one);
  }

  void BLASShift(float* p, const float* q1, const float* q2, unsigned int n) {
    long m=n, one=1, zero=0;
    float fone=1.;
    static char FG[]="L";
    BLAS<float>::SbMv(FG,&m,&zero,&fone,const_cast<float*>(q1),&one,
                      const_cast<float*>(q2),&one,&fone,p,&one);
  }

  void BLASShift(double* p, const double& d, const double* q1, const double* q2,
                 unsigned int n) {
    long m=n, one=1, zero=0;
    double done=1.;
    static char FG[]="L";
    BLAS<double>::SbMv(FG,&m,&zero,const_cast<double*>(&d),
                       const_cast<double*>(q1),&one,
                       const_cast<double*>(q2),&one,&done,p,&one);
  }

  void BLASShift(float* p, const float& d, const float* q1, const float* q2,
                 unsigned int n) {
    long m=n, one=1, zero=0;
    float fone=1.;
    static char FG[]="L";
    BLAS<float>::SbMv(FG,&m,&zero,const_cast<float*>(&d),
                       const_cast<float*>(q1),&one,
                       const_cast<float*>(q2),&one,&fone,p,&one);
  }

}

#endif

