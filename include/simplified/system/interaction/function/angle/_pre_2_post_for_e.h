
#ifndef _System_Interaction_Function_Angle_P2P_forE_H_
#define _System_Interaction_Function_Angle_P2P_forE_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/angle/pre-name.h"
#include "system/interaction/function/angle/post-name.h"

namespace mysimulator {

  void _pre_2_post_for_e_angle(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status,const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    _post[AnglePostName::Cosine]=
      _pre[AnglePreName::DotAB]/
      __square_root(_pre[AnglePreName::EdgeASQ]*_pre[AnglePreName::EdgeBSQ]);
    _status.SetReady4Energy();
  }

}

#endif

