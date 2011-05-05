
#ifndef _Functional_Harmonic_Both_H_
#define _Functional_Harmonic_Both_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/harmonic/parameter/name.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void BothHarmonic(const T& dsq,const UniqueParameter64Bit* prm,T& fc,T& df) {
    T d=sqroot(dsq);
    T Dd=d-prm[HarmonicEqLength].value<T>();
    T tmd=prm[HarmonicEqStrength].value<T>()*Dd;
    fc=tmd*Dd;
    df=(tmd+tmd)/d;
  }

}

#endif

