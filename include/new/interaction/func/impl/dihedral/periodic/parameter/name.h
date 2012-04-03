
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Parameter_Name_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Parameter_Name_H_

#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  enum DihedralPeriodicParameterName {
    DihPeriodicNumFuncs=InteractionCommonNumberParameters,
    DihPeriodicNumParameters,
    DihPeriodicFuncParamShift,
  };

  enum DihedralPeriodicFuncParameterName {
    DihPeriodicFuncStrength=0,
    DihPeriodicFuncFrequence,
    DihPeriodicFuncPhase,
    DihPeriodicFuncStrengthFrequence,
    DihPeriodicFuncNumberParameters
  };

}

#include "interaction/func/impl/dihedral/periodic/parameter/build.h"

#endif

