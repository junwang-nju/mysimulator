
#ifndef _Propagator_Parameter_Name_H_
#define _Propagator_Parameter_Name_H_

namespace mysimulator {

  enum PropagatorParameterName {
    PropagatorTimeStep=0,
    PropagatorKineticEnergy,
    PropagatorMass,
    PropagatorNegHTIM,
    PropagatorVelocitySQ,
    PropagatorFriction,
    PropagatorTemperature,
    PropagatorGaussRNG,
    PropagatorRandVector,
    PropagatorRandSize,
    PropagatorFacBf,
    PropagatorFacAf,
    PropagatorNumberParameter
  };

}

#endif

