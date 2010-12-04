
#ifndef _Functional_FENE_H_
#define _Functional_FENE_H_

#include "data/name/fene.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void FuncFENE(const T& dsq, const UniqueParameter* prm, T& func) {
    T d=sqroot(dsq);
    T Dd=d-prm[FENEEqLength].value<T>();
    func=-prm[FENEHalfStrengthDRadiusSQ].value<T>()*
          ln(1-Dd*Dd*prm[FENEIvDeltaRadiusMaxSQ].value<T>());
  }

  template <typename T>
  void DiffFENE(const T& dsq, const UniqueParameter* prm, T& diff) {
    T d=sqroot(dsq);
    T Dd=d-prm[FENEEqLength].value<T>();
    diff=prm[FENEStrengthDRadiusSQ].value<T>()*
         Dd/(prm[FENEDeltaRadiusMaxSQ].value<T>()-Dd*Dd)/d;
  }

  template <typename T>
  void BothFENE(const T& dsq, const UniqueParameter* prm, T& func, T& diff) {
    T d=sqroot(dsq);
    T Dd=d-prm[FENEEqLength].value<T>();
    T sqDd=Dd*Dd;
    func=-prm[FENEHalfStrengthDRadiusSQ].value<T>()*
          ln(1-sqDd*prm[FENEIvDeltaRadiusMaxSQ].value<T>());
    diff=prm[FENEStrengthDRadiusSQ].value<T>()*
         Dd/(prm[FENEDeltaRadiusMaxSQ].value<T>()-sqDd)/d;
  }

}

#endif
