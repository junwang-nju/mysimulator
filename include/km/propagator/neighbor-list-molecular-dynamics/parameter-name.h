
#ifndef _Propagator_NeighborList_MD_Parameter_Name_H_
#define _Propagator_NeighborList_MD_Parameter_Name_H_

#include "propagator/molecular-dynamics/parameter-name.h"

namespace mysimulator {

  enum PropagatorMDWithNLParameterName {
    PropagatorMDWithNL_TimeStep = PropagatorMD_TimeStep,
    PropagatorMDWithNL_KineticEnergy = PropagatorMD_KineticEnergy,
    PropagatorMDWithNL_Mass = PropagatorMD_Mass,
    PropagatorMDWithNL_NegHTIM = PropagatorMD_NegHTIM,
    PropagatorMDWithNL_VelocitySQ = PropagatorMD_VelocitySQ,
    PropagatorMDWithNL_Friction = PropagatorMD_Friction,
    PropagatorMDWithNL_Temperature = PropagatorMD_Temperature,
    PropagatorMDWithNL_GaussRNG = PropagatorMD_GaussRNG,
    PropagatorMDWithNL_RandVector = PropagatorMD_RandVector,
    PropagatorMDWithNL_RandSize = PropagatorMD_RandSize,
    PropagatorMDWithNL_FacBf = PropagatorMD_FacBf,
    PropagatorMDWithNL_FacAf = PropagatorMD_FacAf,
    PropagatorMDWithNL_RelaxTime = PropagatorMD_RelaxTime,
    PropagatorMDWithNL_ListArray = PropagatorMD_NumberParameter,
    PropagatorMDWithNL_NumberParameter
  };

}

#endif

