
#ifndef _System_Interaction_Parameter_Dihedral_DualPeriodic_CmPhase_Build_H_
#define _System_Interaction_Parameter_Dihedral_DualPeriodic_CmPhase_Build_H_

#include "system/interaction/parameter/dihedral/dual-periodic-common-phase/name.h"
#include "system/interaction/parameter/dihedral/dual-periodic/_build.h"

namespace mysimulator {

  class InteractionParameter;

  void _build_dihedral_dual_periodic_common_phase(
      Array<Double>& _FParam,Array<Int>& _IParam,
      Array<InteractionParameter>& _PParam) {
    assert((bool)_FParam);
    assert(
        _FParam.size()>=
        DihedralDualPeriodicCommonPhaseParameterName::Double::NumberParameter);
    _build_dihedral_dual_periodic(_FParam,_IParam,_PParam);
    _PParam[DihedralDualPeriodicCommonPhaseParameterName::Child::Period1]
           [DihedralPeriodicParameterName::Double::Phase] =
    _FParam[DihedralDualPeriodicCommonPhaseParameterName::Double::Phase];
    _PParam[DihedralDualPeriodicCommonPhaseParameterName::Child::Period2]
           [DihedralPeriodicParameterName::Double::Phase] =
    _FParam[DihedralDualPeriodicCommonPhaseParameterName::Double::Phase];
  }

}

#endif

