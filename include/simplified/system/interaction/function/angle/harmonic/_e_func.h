
#ifndef _System_Interaction_Function_Angle_Harmonic_E_Func_H_
#define _System_Interaction_Function_Angle_Harmonic_E_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/angle/harmonic/post-name.h"

namespace mysimulator {

  void _efunc_angle_harmonic(
      Array<Double> const& _post, InteractionParameter const& P, double *Func) {
    assert((bool)_post);
    assert((bool)P);
    double dA=_post[AngleHarmonicPostName::Angle]-
              P[AngleHarmonicParameterName::EqAngle];
    *Func=P[AngleHarmonicParameterName::EqStrength]*dA*dA;
  }

}

#endif

