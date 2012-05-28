
#ifndef _Propagator_Time_MolecularDynamics_Parameter_Name_H_
#define _Propagator_Time_MolecularDynamics_Parameter_Name_H_

namespace mysimulator {

  enum PropagatorMDTimeParameterName {
    MDTime_TimeStep=0,
    MDTime_NowTime,
    MDTime_NowStep,
    MDTime_TotalPeriod,
    MDTime_NumberStep,
    MDTime_OutputInterval,
    MDTime_NumberStepBwOutput,
    MDTime_NumberOutput,
    MDTime_NumberParameter
  };

}

#endif

