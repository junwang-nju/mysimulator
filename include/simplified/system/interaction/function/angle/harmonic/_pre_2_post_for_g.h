
#ifndef _System_Interaction_Function_Angle_Harmonic_P2P_forG_H_
#define _System_Interaction_Function_Angle_Harmonic_P2P_forG_H_

#include "system/interaction/function/angle/_pre_2_post_for_g.h"
#include "system/interaction/function/angle/harmonic/pre-name.h"
#include "system/interaction/function/angle/harmonic/post-name.h"

namespace mysimulator {

  void _pre_2_post_for_g_angle_harmonic(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status,const InteractionParameter& P) {
    _pre_2_post_for_g_angle(_pre,_post,_status,P);
    _post[AngleHarmonicPostName::Angle] =
      __acos(_post[AngleHarmonicPostName::Cosine]);
  }

}

#endif

