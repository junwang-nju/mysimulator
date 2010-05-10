
#ifndef _Functional_Harmonic_H_
#define _Functional_Harmonic_H_

#include "parameter-name-harmonic.h"
#include "unique-parameter.h"
#include <cmath>

namespace std {

  void FuncHarmonic(const double dsq, const UniqueParameter* prm,
                    double& func) {
    double d=sqrt(dsq);
    double Dd=d-prm[HarmonicEqLength].d;
    func=prm[HarmonicEqStrength].d*Dd*Dd;
  }

  void DiffHarmonic(const double dsq, const UniqueParameter* prm,
                    double& diff) {
    double d=sqrt(dsq);
    double Dd=d-prm[HarmonicEqLength].d;
    diff=prm[HarmonicDualEqStrength].d*Dd/d;
  }

  void BothHarmonic(const double dsq, const UniqueParameter* prm,
                    double& func, double& diff) {
    double d=sqrt(dsq);
    double Dd=d-prm[HarmonicEqLength].d;
    double tmd=prm[HarmonicEqStrength].d*Dd;
    func=tmd*Dd;
    diff=(tmd+tmd)/d;
  }

}

#endif

