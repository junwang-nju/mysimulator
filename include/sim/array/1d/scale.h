
#ifndef _Array_1D_Scale_H_
#define _Array_1D_Scale_H_

namespace mysimulator {

  template <typename T1, typename T2>
  void Scale(T1* p, const T2& d, unsigned int n) {
    for(unsigned int i=0;i<n;++i) p[i]*=d;
  }

  template <typename T1, typename T2>
  void Scale(T1* p, T2* const& q,unsigned int n) {
    for(unsigned int i=0;i<n;++i) p[i]*=q[i];
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void BLASScale(double* p, const double& d, unsigned int n) {
    long m=n, one=1;
    BLAS<double>::Scale(&m,const_cast<double*>(&d),p,&one);
  }

  void BLASScale(float* p, const float& d, unsigned int n) {
    long m=n, one=1;
    BLAS<float>::Scale(&m,const_cast<float*>(&d),p,&one);
  }

  void BLASScale(double* p, const double* q, unsigned int n) {
    long m=n, one=1, zero=0;
    static char FG[]="LNN";
    BLAS<double>::TbMv(FG,FG+1,FG+2,&m,&zero,const_cast<double*>(q),&one,
                       p,&one);
  }

  void BLASScale(float* p, const float* q,unsigned int n) {
    long m=n, one=1, zero=0;
    static char FG[]="LNN";
    BLAS<float>::TbMv(FG,FG+1,FG+2,&m,&zero,const_cast<float*>(q),&one,
                      p,&one);
  }

}

#endif

