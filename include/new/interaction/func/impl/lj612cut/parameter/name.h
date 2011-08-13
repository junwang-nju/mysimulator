
#ifndef _Interaction_Func_Implement_LJ612Cut_Parameter_Name_H_
#define _Interaction_Func_Implement_LJ612Cut_Parameter_Name_H_

namespace mysimulator {

  enum LJ612CutParameterName {
    LJ612CutEqRadius=0,
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

#include "interaction/func/impl/lj612cut/parameter/build.h"

#endif

