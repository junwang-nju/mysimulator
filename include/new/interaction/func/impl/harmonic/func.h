
#ifndef _Interaction_Func_Implement_Harmonic_Func_H_
#define _Interaction_Func_Implement_Harmonic_Func_H_

#include "interaction/func/impl/harmonic/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void FuncHarmonic(const T& dsq, const Unique64Bit* P, T& func) {
    T d=sqroot(dsq);
    T Dd=d-P[HarmonicEqLength].value<T>();
    func=P[HarmonicEqStrength].value<T>()*Dd*Dd;
  }

}

#endif

