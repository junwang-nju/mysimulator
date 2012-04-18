
#ifndef _Array_1D_Swap_H_
#define _Array_1D_Swap_H_

namespace mysimulator {

  template <typename T>
  void Exchange(T*& p, T*& q) {
    T* tm;
    tm=p;   p=q;    q=tm;
  }

  template <typename T>
  void Swap(T* p, T* q, unsigned int n) {
    T tm;
    for(unsigned int i=0;i<n;++i) { tm=p[i];  p[i]=q[i];  q[i]=tm; }
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void BLASSwap(double* p, double* q, unsigned int n) {
    long m=n,one=1;
    BLAS<double>::Swap(&m,const_cast<double*>(p),&one,
                          const_cast<double*>(q),&one);
  }

  void BLASSwap(float* p, float* q, unsigned int n) {
    long m=n,one=1;
    BLAS<float>::Swap(&m,const_cast<float*>(p),&one,
                         const_cast<float*>(q),&one);
  }

}

#endif

