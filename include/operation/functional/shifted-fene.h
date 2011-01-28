
#ifndef _Functional_Shifted_FENE_H_
#define _Functional_Shifted_FENE_H_

#include "data/name/shifted-fene.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void FuncShiftedFENE(const T& dsq, const UniqueParameter* prm, T& func) {
    T d=sqroot(dsq);
    T Dd=d-prm[SfFENEEqLength].value<T>();
    func=-prm[SfFENEHalfStrengthDRadiusSQ].value<T>()*
          ln(1-Dd*Dd*prm[SfFENEIvDeltaRadiusMaxSQ].value<T>());
  }

  template <typename T>
  void DiffShiftedFENE(const T& dsq, const UniqueParameter* prm, T& diff) {
    T d=sqroot(dsq);
    T Dd=d-prm[SfFENEEqLength].value<T>();
    diff=prm[SfFENEStrengthDRadiusSQ].value<T>()*
         Dd/(prm[SfFENEDeltaRadiusMaxSQ].value<T>()-Dd*Dd)/d;
  }

  template <typename T>
  void BothShiftedFENE(const T& dsq, const UniqueParameter* prm,
                       T& func, T& diff) {
    T d=sqroot(dsq);
    T Dd=d-prm[SfFENEEqLength].value<T>();
    T sqDd=Dd*Dd;
    func=-prm[SfFENEHalfStrengthDRadiusSQ].value<T>()*
          ln(1-sqDd*prm[SfFENEIvDeltaRadiusMaxSQ].value<T>());
    diff=prm[SfFENEStrengthDRadiusSQ].value<T>()*
         Dd/(prm[SfFENEDeltaRadiusMaxSQ].value<T>()-sqDd)/d;
  }

}

#endif
