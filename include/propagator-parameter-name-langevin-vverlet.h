
#ifndef _Propagator_Parameter_Name_Langevin_VelocityVerlet_H_
#define _Propagator_Parameter_Name_Langevin_VelocityVerlet_H_

#include "propagator-parameter-name-common.h"

namespace std {

  enum PropagatorMoveNameLV {
    LV_BeforeG=0,
    LV_AfterG,
    NumberMoveLV
  };

  enum PropagatorSetNameLV {
    TemperatureLV=NumberSetCommon,
    ViscosityLV,
    GaussiamRNGPointerLV,
    NumberSetLV
  };

  enum PropagatorParameterNameLV {
    LV_Temperature=NumberParameterCommon,
    LV_Viscosity,
    LV_TemperatureDeltaT,
    LV_GaussianRNGPointer,
    NumberParameterLV
  };

}

#endif

