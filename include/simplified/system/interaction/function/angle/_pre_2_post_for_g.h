
#ifndef _System_Interaction_Function_Angle_P2P_forG_H_
#define _System_Interaction_Function_Angle_P2P_forG_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/angle/pre-name.h"
#include "system/interaction/function/angle/post-name.h"

namespace mysimulator {

  void _pre_2_post_for_g_angle(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status,const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    double tmda=1./_pre[AnglePreName::EdgeASQ];
    double tmdb=1./_pre[AnglePreName::EdgeBSQ];
    double tmd=__square_root(tmda*tmdb);
    double tmd1=tmd*_pre[AnglePreName::DotAB];
    double tmd2=1./__square_root(1.-tmd1*tmd1);
    double tmd3=tmd1*tmd2;
    _post[AnglePostName::Cosine]=tmd1;
    _post[AnglePostName::IvRabSin]=tmd*tmd2;
    _post[AnglePostName::IvRaSQCtg]=tmd3*tmda;
    _post[AnglePostName::IvRbSQCtg]=tmd3*tmdb;
    _status.SetReady4EnergyGradient();
  }

}

#endif

