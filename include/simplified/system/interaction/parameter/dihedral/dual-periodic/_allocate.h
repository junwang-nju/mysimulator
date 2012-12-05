
#ifndef _System_Interaction_Parameter_Dihedral_DualPeriodic_Allocate_H_
#define _System_Interaction_Parameter_Dihedral_DualPeriodic_Allocate_H_

#include "system/interaction/parameter/dihedral/dual-periodic/name.h"
#include "system/interaction/name.h"
#include "array/interface.h"

namespace mysimulator {

  class InteractionParameter;

  void _allocate_param_dihedral_dual_periodic(
      Array<Double>&,Array<Int>&,Array<InteractionParameter>& _PParam) {
    _PParam.allocate(DihedralDualPeriodicParameterName::NumberParameter);
    _PParam[DihedralDualPeriodicParameterName::Period1].allocate(
        InteractionName::DihedralPeriodic);
    _PParam[DihedralDualPeriodicParameterName::Period2].allocate(
        InteractionName::DihedralPeriodic);
  }

}

#endif

