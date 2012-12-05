
#ifndef _System_Interaction_Parameter_Angle_Harmonic_Allocate_H_
#define _System_Interaction_Parameter_Angle_Harmonic_Allocate_H_

#include "array/interface.h"
#include "system/interaction/parameter/angle/harmonic/name.h"

namespace mysimulator {

  class InteractionParameter;

  void _allocate_param_angle_harmonic(
      Array<Double>& _FParam, Array<Int>&, Array<InteractionParameter>&) {
    _FParam.allocate(AngleHarmonicParameterName::NumberParameter);
  }

}

#endif

