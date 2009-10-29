
#ifndef _Propagator_Particle_Langevin_VelVerlet_Index_H_
#define _Propagator_Particle_Langevin_VelVerlet_Index_H_

namespace std {

  enum PropagatorParamTypePLV {
    BasicPLV=0,
    RandomVelocityPLV,
    NumberParamPLV
  };

  enum BasicTypePLV {
    HydrodynamicRadiusPLV=0,
    HfDeltaTIvMPLV,
    FrictionCoefPLV,
    RandomVelocitySizePLV,
    FactorBeforeGPLV,
    FactorAfterGPLV,
    NumberBasicPLV
  };

  enum SetTypePLV {
    SetHydrodynamicRadiusPLV=0,
    NumberSetPLV
  };

}

#endif

