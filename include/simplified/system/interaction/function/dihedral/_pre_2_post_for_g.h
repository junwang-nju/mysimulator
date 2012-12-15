
#ifndef _System_Interaction_Function_Dihedral_P2P_forG_H_
#define _System_Interaction_Function_Dihedral_P2P_forG_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/dihedral/pre-name.h"
#include "system/interaction/function/dihedral/post-name.h"
#include "basic/util/arc-cos.h"

namespace mysimulator {

  void _pre_2_post_for_g_dihedral(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    double tmda=_pre[DihedralPreName::IvNormASQ];
    double tmdb=_pre[DihedralPreName::IvNormBSQ];
    double csDih=_pre[DihedralPreName::DotNormAB]*__square_root(tmda*tmdb);
    _post[DihedralPostName::Angle]=__acos(csDih)*
                                   (_pre[DihedralPreName::CrossNormAB]>0?1:-1);
    double tmd1=_pre[DihedralPreName::AxisSQ];
    double tmd=__square_root(tmd1);
    tmd1=tmd/tmd1;
    _post[DihedralPostName::FactorI] = - tmd*tmda;
    _post[DihedralPostName::FactorJ] = - _pre[DihedralPreName::DotBondAB] *
                                         tmda*tmd1;
    _post[DihedralPostName::FactorK] =   _pre[DihedralPreName::DotBondBC] *
                                         tmdb*tmd1;
    _post[DihedralPostName::FactorL] = tmd*tmdb;
    _status.SetReady4EnergyGradient();
  }

}

#endif

