
#ifndef _System_Interaction_Function_Dihedral_P2P_forEG_H_
#define _System_Interaction_Function_Dihedral_P2P_forEG_H_

#include "system/interaction/function/dihedral/_pre_2_post_for_g.h"

namespace mysimulator {

  void _pre_2_post_for_eg_dihedral(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    _pre_2_post_for_g_dihedral(_pre,_post,_status,P);
  }

}

#endif

