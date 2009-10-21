
#ifndef _Propagator_Berendsen_VelVerlet_Index_H_
#define _Propagator_Berendsen_VelVerlet_Index_H_

namespace std {

  enum PropagatorParamBV {
    BasicBV=0,
    NumberParamBV
  };

  enum BasicTypeBV {
    TemperatureBV=0,
    RelaxTimeBV,
    DegreeFreedomBV,
    DeltaTIvRelaxTBV,
    ScaleFacBV,
    NumberBasicBV
  };

  enum MoveTypeBV {
    BeforeGBV=0,
    AfterGBV,
    PostProcessBV,
    NumberMoveBV
  };

  enum SetTypeBV {
    SetTemperatureBV=0,
    SetRelaxTimeBV,
    NumberSetBV
  };

}

#endif

