
#ifndef _Propagator_Parameter_Name_Common_H_
#define _Propagator_Parameter_Name_Common_H_

namespace mysimulator {

  enum PropagatorParameterNameCommon {
    StartTime=0,
    RunTimeStep,
    TotalTime,
    NowTime,
    NowStepID,
    OutputInterval,
    NumberOutput,
    NumberStepPerOutput,
    StepFuncPtr,
    PropagatorNumberParameterCommon
  };

}

#endif

