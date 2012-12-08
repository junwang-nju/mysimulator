
#ifndef _System_Interaction_Parameter_Dihedral_DualPeriodic_CmPhase_Name_H_
#define _System_Interaction_Parameter_Dihedral_DualPeriodic_CmPhase_Name_H_

#include "system/interaction/parameter/dihedral/dual-periodic/name.h"

namespace mysimulator {

  class DihedralDualPeriodicCommonPhaseParameterName
      : public DihedralDualPeriodicParameterName {

    public:

      class Double {
        public:
          static const unsigned int Phase           = 0;
          static const unsigned int NumberParameter = Phase+1;
      };

  };

  const unsigned int
  DihedralDualPeriodicCommonPhaseParameterName::Double::Phase;
  const unsigned int
  DihedralDualPeriodicCommonPhaseParameterName::Double::NumberParameter;

}

#endif

