
#ifndef _Functional_Quadrupal_Harmonic_H_
#define _Functional_Quadrupal_Harmonic_H_

#include "var-vector.h"
#include "parameter-id.h"

namespace std {

  void FuncFactor_quadrupalharmonic(
      const double& d, const varVector<double>& parm, double& funcfac) {
    double Dd=d-parm[quadharm_EqLength];
    double sqDd=Dd*Dd;
    funcfac=sqDd*(parm[quadharm_EqQuadStrength]*sqDd+
                  parm[quadharm_EqHarmStrength]);
  }

  void DiffFactor_quadrupalharmonic(
      const double& d, const varVector<double>& parm, double& difffac) {
    double Dd=d-parm[quadharm_EqLength];
    difffac=Dd*(parm[quadharm_FourEqQuadStrength]*Dd*Dd+
                parm[quadharm_DualEqHarmStrength])/d;
  }

  void BothFactor_quadrupalharmonic(
      const double& d, const varVector<double>& parm,
      double& funcfac, double& difffac) {
    double Dd=d-parm[quadharm_EqLength];
    double sqDd=Dd*Dd;
    funcfac=sqDd*(parm[quadharm_EqQuadStrength]*sqDd+
                  parm[quadharm_EqHarmStrength]);
    difffac=Dd*(parm[quadharm_FourEqQuadStrength]*sqDd+
                parm[quadharm_DualEqHarmStrength])/d;
  }

}

#endif

