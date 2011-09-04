
#ifndef _Minimizer_Line_Common_Minimal_Step_H_
#define _Minimizer_Line_Common_Minimal_Step_H_

#include "array/1d/content/interface.h"
#include "intrinsic-type/abs-value.h"
#include "intrinsic-type/constant.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  T MinimalStepCalc(const Array1DContent<T>& Loc, const Array1DContent<T>& Dirc,
                    const Array1DContent<unsigned int>& Mask) {
    assert(IsValid(Loc)&&IsValid(Dirc)&&IsValid(Mask));
    assert((Loc.size==Dirc.size)&&(Loc.size==Mask.size));
    T mstep;
    T tmd;
    copy(mstep,0);
    for(unsigned int i=0;i<Mask.size;++i) {
      if(Mask[i]==0)  continue;
      tmd=absval(Loc[i]);
      tmd=(tmd<1.?Dirc[i]:Dirc[i]/tmd);
      mstep+=tmd*tmd;
    }
    return RelativeDelta<T>()*sqroot(Mask.size/mstep);
  }

}

#include "array/2d/content/interface.h"

namespace mysimulator {

  template <typename T>
  T MinimalStepCalc(const Array2DContent<T>& Loc, const Array2DContent<T>& Dirc,
                    const Array2DContent<unsigned int>& Mask) {
    return
    MinimalStepCalc(Loc.base,Dirc.base,Mask.base);
  }

}

#endif

