
#ifndef _Propagator_Minimizer_Line_Tracking_Parameter_Name_H_
#define _Propagator_Minimizer_Line_Tracking_Parameter_Name_H_

#include "propagator/minimizer-line/parameter-name.h"

namespace mysimulator {

  enum PropagatorMinimizerLineTrackingParameterName {
    TrackingLineMin_Step = LineMin_Step,
    TrackingLineMin_SearchScale = LineMin_SearchScale,
    TrackingLineMin_GCalcCount = LineMin_GCalcCount,
    TrackingLineMin_LineTag = LineMin_LineTag,
    TrackingLineMin_ConditionTag = LineMin_ConditionTag,
    TrackingLineMin_MaxStep = LineMin_MaxStep,
    TrackingLineMin_DecreaseFac = LineMin_DecreaseFac,
    TrackingLineMin_CurvatureFac = LineMin_CurvatureFac,
    TrackingLineMin_GradThreshold = LineMin_GradThreshold,
    TrackingLineMin_TrackingFac = LineMin_NumberParameter,
    TrackingLineMin_NumberParameter
  };

}

#endif

