
#ifndef _Functional_Harmonic_Diff_H_
#define _Functional_Harmonic_Diff_H_

#include "unique-parameter/64bit/interface.h"
#include "intrinsic-type/sqroot.h"
#include "functional/harmonic/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void DiffHarmonic(const T& dsq, const UniqueParameter64Bit* prm, T& diff) {
    T d=sqroot(dsq);
    T Dd=d-prm[HarmonicEqLength].value<T>();
    diff=prm[HarmonicDualEqStrength].value<T>()*Dd/d;
  }

}

#endif

