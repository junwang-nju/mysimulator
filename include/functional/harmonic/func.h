
#ifndef _Functional_Harmonic_Func_H_
#define _Functional_Harmonic_Func_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/harmonic/parameter/name.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void FuncHarmonic(const T& dsq, const UniqueParameter64Bit* prm, T& func) {
    T d=sqroot(dsq);
    T Dd=d-prm[HarmoniceqLength].value<T>();
    func=prm[HarmonicEqStrength].value<T>()*Dd*Dd;
  }

}

#endif

