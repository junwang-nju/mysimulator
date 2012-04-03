
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Name_H_

#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  enum LJ612CutParameterName {
    LJ612CutEqRadius=InteractionCommonNumberParameters,
    LJ612CutEqEnergyDepth,
    LJ612CutCutR,
    LJ612CutCutRSQ,
    LJ612CutVc,
    LJ612CutKc,
    LJ612CutRealSigma6,
    LJ612CutRealStrength,
    LJ612CutTwlfRealStrength,
    LJ612CutNumberParameters
  };

}

#include "interaction/func/impl/pairwise/lj612cut/parameter/build.h"

#endif

