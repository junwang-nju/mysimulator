
#ifndef _Propagator_Parameter_Name_Berendsen_VelocityVerlet_H_
#define _Propagator_Parameter_Name_Berendsen_VelocityVerlet_H_

#include "propagator-parameter-name-common.h"

namespace std {

  enum PropagatorParamNameBV {
    BV_Temperature=NumberParamCommon,
    BV_RelaxTime,
    BV_DegreeFreedom,
    BV_DeltaTIvRelaxT,
    BV_ScaleFactor,
    NumberParamBV
  };

  enum PropagatorMoveNameBV {
    BV_BeforeG=0,
    BV_AfterG,
    BV_PostProcess,
    NumberMoveBV
  };

  enum PropagatorSetNameBV {
    TemperatureInBV=0,
    RelaxTimeInBV,
    NumberSetBV
  };

}

#endif

