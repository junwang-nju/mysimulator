
#ifndef _Functional_Harmonic_H_
#define _Functional_Harmonic_H_

#include "operation/parameter/build-param-harmonic.h"
#include <cmath>

namespace std {

  template <typename T>
  void FuncHarmonic(const T& dsq,const UniqueParameter* prm, T& func){
    T d=sqrt(dsq);
    T Dd=d-prm[HarmonicEqLength].d;
    func=prm[HarmonicEqStrength].d*Dd*Dd;
  }

  template <typename T>
  void DiffHarmonic(const T& dsq,const UniqueParameter* prm, T& diff) {
    T d=sqrt(dsq);
    T Dd=d-prm[HarmonicEqLength].d;
    diff=prm[HarmonicDualEqStrength].d*Dd/d;
  }

  template <typename T>
  void BothHarmonic(const T& dsq, const UniqueParameter* prm, T& func, T& diff){
    T d=sqrt(dsq);
    T Dd=d-prm[HarmonicEqLength].d;
    T tmd=prm[HarmonicEqStrength].d*Dd;
    func=tmd*Dd;
    diff=(tmd+tmd)/d;
  }

}

#endif

