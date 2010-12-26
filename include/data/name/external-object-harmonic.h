
#ifndef _Parameter_External_Object_Harmonic_H_
#define _Parameter_External_Object_Harmonic_H_

#include "data/name/external-object-base.h"
#include "data/name/harmonic.h"

namespace std {

  enum ExtObjectHarmonicParameterName {
    ExtObjHarmonicEqLength=ExtObjectBaseNumberParameter+HarmonicEqLength,
    ExtObjHarmonicEqStrength=ExtObjectBaseNumberParameter+HarmonicEqStrength,
    ExtObjHarmonicDualEqStrength=
        ExtObjectBaseNumberParameter+HarmonicDualEqStrength,
    ExtObjHarmonicNumberParameter=
        ExtObjectBaseNumberParameter+HarmonicNumberParameter
  };

}

#endif

