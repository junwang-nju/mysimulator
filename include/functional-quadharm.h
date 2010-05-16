
#ifndef _Functional_QuadrupleHarmonic_H_
#define _Functional_QuadrupleHarmonic_H_

#include "parameter-name-quadharm.h"
#include <cmath>

namespace std {

  void FuncQuadHarm(const double dsq, const UniqueParameter* prm,
                    double& func) {
    double d=sqrt(dsq);
    double Dd=d-prm[QuadHarmEqLength].d;
    double sqDd=Dd*Dd;
    func=sqDd*(prm[QuadHarmEqQuadStrength].d*sqDd+
               prm[QuadHarmEqHarmStrength].d);
  }

  void DiffQuadHarm(const double dsq, const UniqueParameter* prm,
                    double& diff) {
    double d=sqrt(dsq);
    double Dd=d-prm[QuadHarmEqLength].d;
    diff=Dd*(prm[QuadHarmFourEqQuadStrength].d*Dd*Dd+
             prm[QuadHarmTwoEqHarmStrength].d)/d;
  }

  void BothQuadHarm(const double dsq, const UniqueParameter* prm,
                    double& func, double& diff) {
    double d=sqrt(dsq);
    double Dd=d-prm[QuadHarmEqLength].d;
    double sqDd=Dd*Dd;
    func=sqDd*(prm[QuadHarmEqQuadStrength].d*sqDd+
               prm[QuadHarmEqHarmStrength].d);
    diff=Dd*(prm[QuadHarmFourEqQuadStrength].d*sqDd+
             prm[QuadHarmTwoEqHarmStrength].d)/d;
  }

}

#endif

