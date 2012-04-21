
#ifndef _Array_1D_Scale_H_
#define _Array_1D_Scale_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void Scale(Array1D<T1>& V, const T2& d,unsigned int n) {
    assert(n<=V.Size());
    for(unsigned int i=0;i<n;++i)   V[i]*=d;
  }

  template <typename T1,typename T2>
  void Scale(Array1D<T1>& V, const Array1D<T2>& V2,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i)   V[i]*=V2[i];
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void BlasScale(Array1D<double>& V,const double& d,unsigned int n) {
    assert(n<=V.Size());
    long m=n, one=1;
    BLAS<double>::Scale(&m,const_cast<double*>(&d),V._data,&one);
  }

  void BlasScale(Array1D<float>& V,const float& d,unsigned int n) {
    assert(n<=V.Size());
    long m=n, one=1;
    BLAS<float>::Scale(&m,const_cast<float*>(&d),V._data,&one);
  }

  void BlasScale(Array1D<double>& V,const Array1D<double>& V2,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    long m=n, one=1, zero=0;
    static char FG[]="LNN";
    BLAS<double>::TbMv(FG,FG+1,FG+2,&m,&zero,const_cast<double*>(V2._data),
                       &one,V._data,&one);
  }

  void BlasScale(Array1D<float>& V,const Array1D<float>& V2,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    long m=n, one=1, zero=0;
    static char FG[]="LNN";
    BLAS<float>::TbMv(FG,FG+1,FG+2,&m,&zero,const_cast<float*>(V2._data),
                       &one,V._data,&one);
  }

}

#endif

