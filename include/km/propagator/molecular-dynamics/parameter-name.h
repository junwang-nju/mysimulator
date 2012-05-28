
#ifndef _Propagator_MolecularDynamics_Parameter_Name_H_
#define _Propagator_MolecularDynamics_Parameter_Name_H_

namespace mysimulator {

  enum PropagatorMDParameterName {
    PropagatorMD_TimeStep = 0,
    PropagatorMD_KineticEnergy,
    PropagatorMD_Mass,
    PropagatorMD_NegHTIM,
    PropagatorMD_VelocitySQ,
    PropagatorMD_Friction,
    PropagatorMD_Temperature,
    PropagatorMD_GaussRNG,
    PropagatorMD_RandVector,
    PropagatorMD_RandSize,
    PropagatorMD_FacBf,
    PropagatorMD_FacAf,
    PropagatorMD_RelaxTime,
    PropagatorMD_NumberParameter
  };

}

#endif

