
#ifndef _Parameter_Subsystem_Propagator_Base_H_
#define _Parameter_Subsystem_Propagator_Base_H_

namespace std {

  enum subsysPropagatorBaseParameterName {
    SubsysMoveMode=0,
    SubsysEnsembleMode,
    TimeStep,
    HalfTimeStep,
    PropagateTrigger,
    PropagateTriggerStep,
    subsysPgBuild,
    subsysPropagatorBaseNumberParameter
  };

}

#endif

