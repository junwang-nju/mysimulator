
#ifndef _System_Interaction_Parameter_Dihedral_DualPeriodic_Build_H_
#define _System_Interaction_Parameter_Dihedral_DualPeriodic_Build_H_

#include "system/interaction/parameter/dihedral/dual-periodic/name.h"
#include "array/interface.h"

namespace mysimulator {

  class InteractionParameter;

  void _build_dihedral_dual_periodic(
      Array<Double>&,Array<Int>&,Array<InteractionParameter>& _PParam) {
    assert((bool)_PParam);
    assert(_PParam.size()>=DihedralDualPeriodicParameterName::NumberParameter);
    _PParam[DihedralDualPeriodicParameterName::Period1].build();
    _PParam[DihedralDualPeriodicParameterName::Period2].build();
  }

}

#endif

