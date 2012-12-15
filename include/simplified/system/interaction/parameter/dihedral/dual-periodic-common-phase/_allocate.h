
#ifndef _System_Interaction_Parameter_Dihedral_DualPeriodic_CmPhase_Allocate_H_
#define _System_Interaction_Parameter_Dihedral_DualPeriodic_CmPhase_Allocate_H_

#include "system/interaction/parameter/dihedral/dual-periodic-common-phase/name.h"
#include "system/interaction/parameter/dihedral/dual-periodic/_allocate.h"

namespace mysimulator {

  class InteractionParameter;

  void _allocate_param_dihedral_dual_periodic_common_phase(
      Array<Double>& _FParam,Array<Int>& _IParam,
      Array<InteractionParameter>& _PParam) {
    _allocate_param_dihedral_dual_periodic(_FParam,_IParam,_PParam);
    _FParam.allocate(
        DihedralDualPeriodicCommonPhaseParameterName::Double::NumberParameter);
  }

}

#endif

