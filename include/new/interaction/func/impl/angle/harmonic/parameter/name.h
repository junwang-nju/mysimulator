
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Parameter_Name_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Parameter_Name_H_

#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  enum AngleHarmonicParameterName {
    AngHarmonicEqAngle=InteractionCommonNumberParameters,
    AngHarmonicStrength,
    AngHarmonicDualStrength,
    AngleHarmonicNumberParameters
  };

}

#include "interaction/func/impl/angle/harmonic/parameter/build.h"

#endif

