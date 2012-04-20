
#ifndef _Array_1D_Shift_H_
#define _Array_1D_Shift_H_

#include "array/1d/size.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void Shift(T1* p, const T2& d) {
    unsigned int n=size(p);
    for(unsigned int i=0;i<n;++i) p[i]+=d;
  }

  template <typename T1, typename T2>
  void Shift(T1* p, const T2* q) {
    unsigned int n=size(p);
    assert(n==size(q));
    for(unsigned int i=0;i<n;++i) p[i]+=q[i];
  }

  template <typename T1, typename T2, typename T3>
  void Shift(T1* p, const T2& d, const T3* q) {
    unsigned int n=size(p);
    assert(n==size(q));
    for(unsigned int i=0;i<n;++i) p[i]+=d*q[i];
  }

  template <typename T1, typename T2, typename T3>
  void Shift(T1* p, const T2* q, const T3& d) { Shift(p,d,q); }

  template <typename T1, typename T2, typename T3>
  void Shift(T1* p, const T2* q1, const T2* q2) {
    unsigned int n=size(p);
    assert((n==size(q1))&&(n==size(q2)));
    for(unsigned int i=0;i<n;++i) p[i]+=q1[i]*q2[i];
  }

  template <typename T1, typename T2, typename T3, typename T4>
  void Shift(T1* p, const T2& d, const T3* q1, const T4* q2) {
    unsigned int n=size(p);
    assert((n==size(q1))&&(n==size(q2)));
    for(unsigned int i=0;i<n;++i) p[i]+=d*q1[i]*q2[i];
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void Shift(double* p, const double& d) {
    long n=size(p), one=1, zero=0;
    double done=1.;
    BLAS<double>::Shift(&n,&done,const_cast<double*>(&d),&zero,p,&one);
  }

  void Shift(float* p, const float& d) {
    long n=size(p), one=1, zero=0;
    float fone=1.;
    BLAS<float>::Shift(&n,&fone,const_cast<float*>(&d),&zero,p,&one);
  }

  void Shift(double* p, const double* q) {
    long n=size(p), one=1;
    assert(static_cast<unsigned int>(n)==size(q));
    double done=1.;
    BLAS<double>::Shift(&n,&done,const_cast<double*>(q),&one,p,&one);
  }

  void Shift(float* p, const float* q) {
    long n=size(p), one=1;
    assert(static_cast<unsigned int>(n)==size(q));
    float fone=1.;
    BLAS<float>::Shift(&n,&fone,const_cast<float*>(q),&one,p,&one);
  }

  void Shift(double* p, const double& d, const double* q) {
    long n=size(p), one=1;
    assert(static_cast<unsigned int>(n)==size(q));
    BLAS<double>::Shift(&n,const_cast<double*>(&d),
                        const_cast<double*>(q),&one,p,&one);
  }

  void Shift(float* p, const float& d, const float* q) {
    long n=size(p), one=1;
    assert(static_cast<unsigned int>(n)==size(q));
    BLAS<float>::Shift(&n,const_cast<float*>(&d),
                       const_cast<float*>(q),&one,p,&one);
  }

  void Shift(double* p, const double* q1, const double* q2) {
    long n=size(p), one=1, zero=0;
    assert(static_cast<unsigned int>(n)==size(q1));
    assert(static_cast<unsigned int>(n)==size(q2));
    double done=1.;
    static char FG[]="L";
    BLAS<double>::SbMv(FG,&n,&zero,&done,const_cast<double*>(q1),&one,
                       const_cast<double*>(q2),&one,&done,p,&one);
  }

  void Shift(float* p, const float* q1, const float* q2) {
    long n=size(p), one=1, zero=0;
    assert(static_cast<unsigned int>(n)==size(q1));
    assert(static_cast<unsigned int>(n)==size(q2));
    float fone=1.;
    static char FG[]="L";
    BLAS<float>::SbMv(FG,&n,&zero,&fone,const_cast<float*>(q1),&one,
                      const_cast<float*>(q2),&one,&fone,p,&one);
  }

  void Shift(double* p, const double& d, const double* q1, const double* q2) {
    long n=size(p), one=1, zero=0;
    assert(static_cast<unsigned int>(n)==size(q1));
    assert(static_cast<unsigned int>(n)==size(q2));
    double done=1.;
    static char FG[]="L";
    BLAS<double>::SbMv(FG,&n,&zero,const_cast<double*>(&d),
                       const_cast<double*>(q1),&one,
                       const_cast<double*>(q2),&one,&done,p,&one);
  }

  void Shift(float* p, const float& d, const float* q1, const float* q2) {
    long n=size(p), one=1, zero=0;
    assert(static_cast<unsigned int>(n)==size(q1));
    assert(static_cast<unsigned int>(n)==size(q2));
    float fone=1.;
    static char FG[]="L";
    BLAS<float>::SbMv(FG,&n,&zero,const_cast<float*>(&d),
                       const_cast<float*>(q1),&one,
                       const_cast<float*>(q2),&one,&fone,p,&one);
  }

}

#endif

