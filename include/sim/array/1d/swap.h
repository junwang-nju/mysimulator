
#ifndef _Array_1D_Swap_H_
#define _Array_1D_Swap_H_

namespace mysimulator {

  template <typename T>
  void Exchange(T*& p, T*& q) {
    T* tm;
    tm=p;   p=q;    q=tm;
  }

}

#include "array/1d/size.h"
#include <cassert>

namespace mysimulator {

  template <typename T>
  void Swap(T* p, T* q) {
    unsigned int n=size(p);
    assert(n==size(q));
    T tm;
    for(unsigned int i=0;i<n;++i) { tm=p[i];  p[i]=q[i];  q[i]=tm; }
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void Swap(double* p, double* q) {
    long n=size(p),one=1;
    assert(static_cast<unsigned int>(n)==size(q));
    BLAS<double>::Swap(&n,const_cast<double*>(p),&one,
                          const_cast<double*>(q),&one);
  }

  void Swap(float* p, float* q) {
    long n=size(p),one=1;
    assert(static_cast<unsigned int>(n)==size(q));
    BLAS<float>::Swap(&n,const_cast<float*>(p),&one,
                         const_cast<float*>(q),&one);
  }

}

#endif

