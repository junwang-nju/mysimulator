
#ifndef _Interaction_Func_Impl_Dihedral_Periodic_Parameter_Name_H_
#define _Interaction_Func_Impl_Dihedral_Periodic_Parameter_Name_H_

namespace mysimulator {

  enum DihedralPeriodicParameterName {
    DihedralPeriodicNumFuncs=0,
    DihedralPeriodicNumParameters,
    DihedralPeriodicFuncParamShift
  };

  enum DihedralPeriodicFuncParameterName {
    DihedralPeriodicFuncStrength=0,
    DihedralPeriodicFuncFrequency,
    DihedralPeriodicFuncPhase,
    DihedralPeriodicFuncStrengthFrequency,
    DihedralPeriodicFuncNumberParameters
  };

}

#include "interaction/func/impl/dihedral/periodic/parameter/build.h"

#endif

