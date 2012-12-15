
#ifndef _System_Interaction_Function_Angle_Harmonic_EG_Func_H_
#define _System_Interaction_Function_Angle_Harmonic_EG_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/angle/harmonic/post-name.h"

namespace mysimulator {

  void _egfunc_angle_harmonic(
      Array<Double> const& _post, InteractionParameter const& P,
      double *Func, double *Diff) {
    assert((bool)_post);
    assert((bool)P);
    double dA=_post[AngleHarmonicPostName::Angle]-
              P[AngleHarmonicParameterName::EqAngle];
    double tmd=dA*P[AngleHarmonicParameterName::EqStrength];
    *Func=tmd*dA;
    *Diff=tmd+tmd;
  }

}

#endif

