
#ifndef _Minimizer_Line_Common_Get_MinimalStep_H_
#define _Minimizer_Line_Common_Get_MinimalStep_H_

#include "array/1d/content/interface.h"
#include "intrinsic-type/constant.h"
#include "intrinsic-type/abs-value.h"
#include "intrinsic-type/square-root.h"
#include "intrinsic-type/square.h"

namespace mysimulator {

  template <typename T>
  T getMinimalStep(const Array1DContent<T>& X, const Array1DContent<T>& V,
                   const unsigned int& DOF) {
    assert(IsValid(X)&&IsValid(V));
    unsigned int n=X.size;
    assert(n==V.size);
    T mstep,tmd,tmd1;
    copy(mstep,cZero);
    T* pX=const_cast<T*>(X.start);
    T* pV=const_cast<T*>(V.start);
    T* pXend=pX+n;
    for(;pX!=pXend;) {
      tmd=absval(*(pX++));
      tmd1=(*(pV++));
      tmd=(tmd<1?tmd1:tmd1/tmd);
      mstep+=square(tmd);
    }
    return RelativeDelta<T>()*sqroot(DOF/mstep);
  }

}

#include "array/2d/content/interface.h"

namespace mysimulator {

  template <typename T>
  T getMinimalStep(const Array2DContent<T>& X, const Array2DContent<T>& V,
                   const unsigned int& DOF) {
    return getMinimalStep(X.base,V.base,DOF);
  }

}

#endif

