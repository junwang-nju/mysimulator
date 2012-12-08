
#ifndef _System_Interaction_Function_Dihedral_P2P_forE_H_
#define _System_Interaction_Function_Dihedral_P2P_forE_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/dihedral/pre-name.h"
#include "system/interaction/function/dihedral/post-name.h"
#include "basic/util/arc-cos.h"

namespace mysimulator {

  void _pre_2_post_for_e_dihedral(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status,const InteractionParameter& P) {
    double csDih=_pre[DihedralPreName::DotNormAB] *
                 __square_root(_pre[DihedralPreName::IvNormASQ] *
                               _pre[DihedralPreName::IvNormBSQ]);
    _post[DihedralPostName::Angle]= __acos(csDih) *
                                    (_pre[DihedralPreName::CrossNormAB]>0?:1-1);
    _status.SetReady4Energy();
  }

}

#endif

