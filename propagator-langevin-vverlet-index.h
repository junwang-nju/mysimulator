
#ifndef _Propagator_Langevin_VelVerlet_Index_H_
#define _Propagator_Langevin_VelVerlet_Index_H_

namespace std {

  enum PropagatorParamTypeLV {
    BasicLV=0,
    NumberParamLV
  };

  enum BasicTypeLV {
    ViscosityCoefLV=0,
    TemperatureLV,
    TempeDeltaTLV,
    NumberBasicLV
  };

}

#endif

