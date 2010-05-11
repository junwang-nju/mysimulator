
#ifndef _Functional_Quadruple_plus_Harmonic_H_
#define _Functional_Quadruple_plus_Harmonic_H_

#include "vector-base.h"
#include "parameter-name-quadplusharm.h"
#include <cmath>

namespace std {

  void FuncQuadPlusHarm(const double dsq, const VectorBase<double>& Prm,
                        double& func) {
    double d=sqrt(dsq);
    double Dd=d-Prm[QuadPlusHarm_EqLength];
    double sqDd=Dd*Dd;
    func=sqDd*(Prm[QuadPlusHarm_EqQuadStrength]*sqDd+
               Prm[QuadPlusHarm_EqHarmStrength]);
  }

  void DiffQuadPlusHarm(const double dsq, const VectorBase<double>& Prm,
                        double& diff) {
    double d=sqrt(dsq);
    double Dd=d-Prm[QuadPlusHarm_EqLength];
    diff=Dd*(Prm[QuadPlusHarm_FourEqQuadStrength]*Dd*Dd+
             Prm[QuadPlusHarm_DualEqHarmStrength])/d;
  }

  void BothQuadPlusHarm(const double dsq, const VectorBase<double>& Prm,
                        double& func, double& diff) {
    double d=sqrt(dsq);
    double Dd=d-Prm[QuadPlusHarm_EqLength];
    double sqDd=Dd*Dd;
    func=sqDd*(Prm[QuadPlusHarm_EqQuadStrength]*sqDd+
               Prm[QuadPlusHarm_EqHarmStrength]);
    diff=Dd*(Prm[QuadPlusHarm_FourEqQuadStrength]*Dd*Dd+
             Prm[QuadPlusHarm_DualEqHarmStrength])/d;
  }

}

#endif

