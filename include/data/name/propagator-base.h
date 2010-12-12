
#ifndef _Parameter_Propagator_Base_H_
#define _Parameter_Propagator_Base_H_

namespace std {

  enum PropagatorBaseParameterName {
    MoveMode=0,
    StartTime,
    RunTimeStep,
    TotalTime,
    NowTime,
    NowStepID,
    OutputInterval,
    NumberOutput,
    NumberStepInOneOutput,
    PgStep,
    PgOutput,
    PropagatorBaseNumberParameter
  };

}

#endif

