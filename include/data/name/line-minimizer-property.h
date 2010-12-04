
#ifndef _Line_Minimizer_Property_Name_H_
#define _Line_Minimizer_Property_Name_H_

#include "minimizer-property.h"

namespace std {

  enum LineMinimizerPropertyName {
    LineSearchCount=MinimizerNumberProperty,
    RunningEnergy,
    RunningProject,
    DecreaseFactor,
    CurvatureFactor,
    GradientThreshold,
    LineMinimizerNumberProperty
  };

}

#endif
