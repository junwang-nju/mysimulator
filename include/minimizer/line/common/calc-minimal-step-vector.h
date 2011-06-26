
#ifndef _Minimizer_Line_Common_Calc_MinimalStep_Vector_H_
#define _Minimizer_Line_Common_Calc_MinimalStep_Vector_H_

#include "minimizer/line/common/interface.h"
#include "vector/interface.h"
#include "intrinsic-type/abs-value.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  T CalcMinimalStep(const Vector<T>& X, const Vector<T>& D,
                    const Vector<unsigned int>& M, const unsigned int& F) {
    assert(IsValid(X)&&IsValid(D)&&IsValid(M));
    T mstep;
    T tmd;
    copy(mstep,0.);
    for(unsigned int i=0;i<M.size;++i) {
      if(M[i]==0)    continue;
      tmd=absval(X[i]);
      tmd=(tmd<1.?D[i]:D[i]/tmd);
      mstep+=tmd*tmd;
    }
    return RelativeDelta<T>()*sqroot(F/mstep);
  }

}

#endif

