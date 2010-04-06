
#ifndef _Propagator_Parameter_Name_ConstantE_VelocityVerlet_H_
#define _Propagator_Parameter_Name_ConstantE_VelocityVerlet_H_

#include "propagator-parameter-name-common.h"

namespace std {

  enum PropagatorParamNameEV {
    NumberParamEV=NumberParamCommon
  };

  enum PropagatorMoveNameEV {
    EV_BeforeG=0,
    EV_AfterG,
    NumberMoveEV
  };

  enum PropagatorSetNameEV {
    NumberSetEV=0
  };

}

#endif

