
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Parameter_Name_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Parameter_Name_H_

#include "interaction/func/impl/dihedral/common/parameter/name.h"

namespace mysimulator {

  enum DihedralPeriodicParameterName {
    DihedralPeriodicNumFuncs=DihedralCommonNumberParameters,
    DihedralPeriodicNumParameters,
    DihedralPeriodicFuncParamShift,
  };

  enum DihedralPeriodicFuncParameterName {
    DihedralPeriodicFuncStrength=0,
    DihedralPeriodicFuncFrequence,
    DihedralPeriodicFuncPhase,
    DihedralPeriodicFuncStrengthFrequence,
    DihedralPeriodicFuncNumberParameters
  };

}

#include "interaction/func/impl/dihedral/periodic/parameter/build.h"

#endif

