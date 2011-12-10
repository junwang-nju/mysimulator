
#ifndef _Interaction_Func_Implement_LJ1012Cut_Parameter_Name_H_
#define _Interaction_Func_Implement_LJ1012Cut_Parameter_Name_H_

namespace mysimulator {

  enum LJ1012CutParameterName {
    LJ1012CutEqRadius=0,
    LJ1012CutEqEnergyDepth,
    LJ1012CutCutR,
    LJ1012CutCutSQ,
    LJ1012CutRealEnergyDepth,
    LJ1012CutRealRadiusSQ,
    LJ1012CutSixtyRealEnergyDepth,
    LJ1012CutVc,
    LJ1012CutKc,
    LJ1012CutNumberParameter
  };

}

#include "interaction/func/impl/lj1012cut/parameter/build.h"

#endif

