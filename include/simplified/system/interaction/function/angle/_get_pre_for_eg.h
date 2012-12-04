
#ifndef _System_Interaction_Function_Angle_GetPre_forEG_H_
#define _System_Interaction_Function_Angle_GetPre_forEG_H_

#include "system/interaction/function/angle/_get_pre_for_e.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM>
  void _get_pre_for_eg_angle(
      Array<InteractionFunction<GT,DIM>*> const& _neighbor,
      Array<Double>& _pre) {
    _get_pre_for_e_angle(_neighbor,_pre);
  }

}

#endif

