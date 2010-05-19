
#ifndef _Propagator_Parameter_Name_Berendsen_VelocityVerlet_H_
#define _Propagator_Parameter_Name_Berendsen_VelocityVerlet_H_

#include "propagator-parameter-name-common.h"

namespace std {

  enum PropagatorMoveNameBV {
    BV_BeforeG=0,
    BV_AfterG,
    BV_PostProcess,
    NumberMoveBV
  };

  enum PropagatorSetNameBV {
    TemperatureBV=NumberSetCommon,
    RelaxTimeBV,
    NumberSetBV
  };

  enum PropagatorParameterNameBV {
    BV_Temperature=NumberParameterCommon,
    BV_RelaxTime,
    BV_DegreeFreedom,
    BV_DeltaTIvRelaxT,
    BV_ScaleFactor,
    NumberParameterBV
  };

}

#endif

