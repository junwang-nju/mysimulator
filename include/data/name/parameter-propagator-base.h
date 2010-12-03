
#ifndef _Parameter_Propagator_Base_H_
#define _Parameter_Propagator_Base_H_

namespace std {

  enum PropagatorBaseParameterName {
    PropagatorMode=0,
    DeltaTime,
    HalfDeltaTime,
    StartTime,
    NowTime,
    TotalTime,
    OutputInterval,
    CountOutput,
    CountStepsInOutput,
    PropagatorBaseNumberParameter
  };

}

#endif

