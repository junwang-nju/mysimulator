
#ifndef _Propagator_Parameter_Name_Langevin_VelocityVerlet_H_
#define _Propagator_Parameter_Name_Langevin_VelocityVerlet_H_

#include "propagator-parameter-name-common.h"

namespace std {

  enum PropagatorParamNameLV {
    LV_Temperature=NumberParamCommon,
    LV_ViscosityCoef,
    LV_TemperatureDeltaT,
    LV_GaussianRNGPointer,
    NumberParamLV
  };

  enum PropagatorMoveNameLV {
    LV_BeforeG=0,
    LV_AfterG,
    NumberMoveLV
  };

  enum PropagatorSetNameLV {
    TemperatureInLV=NumberSetCommon,
    ViscosityInLV,
    GaussianRNGPointerInLV,
    NumberSetLV
  };

}

#endif

