
#ifndef _Array_1D_ScaleCopy_H_
#define _Array_1D_ScaleCopy_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T1,typename T2,typename T3>
  void ScaleCopy(Array1D<T1>& V,const T2& d,const Array1D<T3>& V2,
                 unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i)   V[i]=d*V2[i];
  }
  template <typename T1,typename T2,typename T3>
  void ScaleCopy(Array1D<T1>& V,const Array1D<T2>& V2,const T3& d,
                 unsigned int n) { ScaleCopy(V,d,V2,n); }

}

#include "array/1d/copy.h"
#include "array/1d/scale.h"

namespace mysimulator {

  template <typename T>
  void BlasScaleCopy(Array1D<T>& V,const T& d,const Array1D<T>& V2,
                     unsigned int n) {
    BlasCopy(V,V2,n);
    BlasScale(V,d,n);
  }
  template <typename T>
  void BlasScaleCopy(Array1D<T>& V,const Array1D<T>& V2,const T& d,
                     unsigned int n) { BlasScaleCopy(V,d,V2,n); }

  template <typename T>
  void MemScaleCopy(Array1D<T>& V,const T& d,const Array1D<T>& V2,
                    unsigned int n) {
    MemCopy(V,V2,n);
    Scale(V,d,n);
  }
  template <typename T>
  void MemScaleCopy(Array1D<T>& V,const Array1D<T>& V2,const T& d,
                    unsigned int n) { MemScaleCopy(V,d,V2,n); }

}

#endif

