
#ifndef _System_Interaction_Parameter_Dihedral_DualPeriodic_Allocate_H_
#define _System_Interaction_Parameter_Dihedral_DualPeriodic_Allocate_H_

#include "system/interaction/parameter/dihedral/dual-periodic/name.h"
#include "system/interaction/name.h"
#include "array/interface.h"

namespace mysimulator {

  class InteractionParameter;

  void _allocate_param_dihedral_dual_periodic(
      Array<Double>&,Array<Int>& _IParam,Array<InteractionParameter>& _PParam) {
    _IParam.allocate(DihedralDualPeriodicParameterName::Int::NumberParameter);
    _IParam[DihedralDualPeriodicParameterName::Int::NumberChild]=
      DihedralDualPeriodicParameterName::Child::NumberParameter;
    _PParam.allocate(DihedralDualPeriodicParameterName::Child::NumberParameter);
    _PParam[DihedralDualPeriodicParameterName::Child::Period1].allocate(
        InteractionName::DihedralPeriodic);
    _PParam[DihedralDualPeriodicParameterName::Child::Period2].allocate(
        InteractionName::DihedralPeriodic);
  }

}

#endif

