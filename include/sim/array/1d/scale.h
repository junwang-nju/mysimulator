
#ifndef _Array_1D_Scale_H_
#define _Array_1D_Scale_H_

#include "array/1d/size.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void Scale(T1* p, const T2& d) {
    unsigned int n=size(p);
    for(unsigned int i=0;i<n;++i) p[i]*=d;
  }

  template <typename T1, typename T2>
  void Scale(T1* p, const T2* q) {
    unsigned int n=size(p);
    assert(n==size(q));
    for(unsigned int i=0;i<n;++i) p[i]*=q[i];
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void Scale(double* p, const double& d) {
    long n=size(p), one=1;
    BLAS<double>::Scale(&n,const_cast<double*>(&d),p,&one);
  }

  void Scale(float* p, const float& d) {
    long n=size(p), one=1;
    BLAS<float>::Scale(&n,const_cast<float*>(&d),p,&one);
  }

  void Scale(double* p, const double* q) {
    long n=size(p), one=1, zero=0;
    static char FG[]="LNN";
    assert(static_cast<unsigned int>(n)==size(q));
    BLAS<double>::TbMv(FG,FG+1,FG+2,&n,&zero,const_cast<double*>(q),&one,
                       p,&one);
  }

  void Scale(float* p, const float* q) {
    long n=size(p), one=1, zero=0;
    static char FG[]="LNN";
    assert(static_cast<unsigned int>(n)==size(q));
    BLAS<float>::TbMv(FG,FG+1,FG+2,&n,&zero,const_cast<float*>(q),&one,
                      p,&one);
  }

}

#endif

