
#ifndef _System_Interaction_Parameter_Angle_Harmonic_Build_H_
#define _System_Interaction_Parameter_Angle_Harmonic_Build_H_

#include "system/interaction/parameter/angle/harmonic/name.h"
#include "array/interface.h"

namespace mysimulator {

  void _build_angle_harmonic(Array<Double>& _FParam, Array<Int>&) {
    assert((bool)_FParam);
    assert(_FParam.size()>=AngleHarmonicParameterName::NumberParameter);
    _FParam[AngleHarmonicParameterName::DualEqStrength] =
      2 * _FParam[AngleHarmonicParameterName::EqStrength];
  }

}

#endif

