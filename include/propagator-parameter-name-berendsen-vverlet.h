
#ifndef _Propagator_Parameter_Name_Berendsen_VelocityVerlet_H_
#define _Propagator_Parameter_Name_Berendsen_VelocityVerlet_H_

#include "propagator-parameter-name-common.h"

namespace std {

  enum PropagatorMoveNameBV {
    BV_PreProcess=0,
    BV_BeforeG,
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
    BV_HalfDeltaTIvRelaxT,
    BV_BScaleFactor,
    BV_AScaleFactor,
    BV_TemperatureDOF,
    BV_MassVelSq,
    BV_TemperatureDOFIvKE,
    BV_IvHalfDeltaTIvRelaxTPlus1,
    NumberParameterBV
  };

}

#endif

