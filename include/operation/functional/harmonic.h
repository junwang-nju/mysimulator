
#ifndef _Functional_Harmonic_H_
#define _Functional_Harmonic_H_

#include "data/name/parameter-harmonic.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void FuncHarmonic(const T& dsq,const UniqueParameter* prm, T& func){
    T d=sqroot(dsq);
    T Dd=d-prm[HarmonicEqLength].value<T>();
    func=prm[HarmonicEqStrength].value<T>()*Dd*Dd;
  }

  template <typename T>
  void DiffHarmonic(const T& dsq,const UniqueParameter* prm, T& diff) {
    T d=sqroot(dsq);
    T Dd=d-prm[HarmonicEqLength].value<T>();
    diff=prm[HarmonicDualEqStrength].value<T>()*Dd/d;
  }

  template <typename T>
  void BothHarmonic(const T& dsq, const UniqueParameter* prm, T& func, T& diff){
    T d=sqroot(dsq);
    T Dd=d-prm[HarmonicEqLength].value<T>();
    T tmd=prm[HarmonicEqStrength].value<T>()*Dd;
    func=tmd*Dd;
    diff=(tmd+tmd)/d;
  }

}

#endif

