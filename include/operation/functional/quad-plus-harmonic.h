
#ifndef _Functional_Quadruple_Plus_Harmonic_H_
#define _Functional_Quadruple_Plus_Harmonic_H_

#include "data/name/parameter-quad-plus-harmonic.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void FuncQuadHarmonic(const T& dsq, const UniqueParameter* prm, T& func){
    T d=sqroot(dsq);
    T Dd=d-prm[QuadHarmonicEqLength].value<T>();
    T sqDd=Dd*Dd;
    func=sqDd*(prm[QuadHarmonicEqQuadStrength].value<T>()*sqDd+
               prm[QuadHarmonicEqHarmonicStrength].value<T>());
  }

  template <typename T>
  void DiffQuadHarmonic(const T& dsq, const UniqueParameter* prm, T& diff) {
    T d=sqroot(dsq);
    T Dd=d-prm[QuadHarmonicEqLength].value<T>();
    diff=Dd*(prm[QuadHarmonicFourEqQuadStrength].value<T>()*Dd*Dd+
             prm[QuadHarmonicTwoEqHarmonicStrength].value<T>())/d;
  }

  template <typename T>
  void BothQuadHarmonic(const T& dsq, const UniqueParameter* prm,
                        T& func, T& diff) {
    T d=sqroot(dsq);
    T Dd=d-prm[QuadHarmonicEqLength].value<T>();
    T sqDd=Dd*Dd;
    func=sqDd*(prm[QuadHarmonicEqQuadStrength].value<T>()*sqDd+
               prm[QuadHarmonicEqHarmonicStrength].value<T>());
    diff=Dd*(prm[QuadHarmonicFourEqQuadStrength].value<T>()*Dd*Dd+
             prm[QuadHarmonicTwoEqHarmonicStrength].value<T>())/d;
  }

}

#endif
