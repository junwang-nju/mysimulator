
#ifndef _Array_1D_ScaleCopy_H_
#define _Array_1D_ScaleCopy_H_

namespace mysimulator {

  template <typename T1,typename T2,typename T3>
  void ScaleCopy(T1* p, const T2* q, const T3& d, unsigned int n) {
    for(unsigned int i=0;i<n;++i) p[i]=d*q[i];
  }

  template <typename T1,typename T2,typename T3>
  void ScaleCopy(T1*  p, const T2& d, const T3* q, unsigned int n) {
    ScaleCopy(p,q,d,n);
  }

}

#include "array/1d/copy.h"
#include "array/1d/scale.h"

namespace mysimulator {

  template <typename T>
  void BLASScaleCopy(T* p, const T* q, const T& d, unsigned int n) {
    BLASCopy(p,q,n);
    BLASScale(p,d,n);
  }

  template <typename T>
  void BLASScaleCopy(T* p, const T& d, const T* q, unsigned int n) {
    BLASScaleCopy(p,q,d,n);
  }

  template <typename T>
  void MemScaleCopy(T* p, const T* q, const T& d, unsigned int n) {
    MemCopy(p,q,n);
    Scale(p,d,n);
  }

  template <typename T>
  void MemScaleCopy(T* p, const T& d, const T* q, unsigned int n) {
    MemScaleCopy(p,q,d,n);
  }

}

#endif

