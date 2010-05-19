
#ifndef _Propagator_Parameter_Name_Common_H_
#define _Propagator_Parameter_Name_Common_H_

namespace std {

  enum PropagatorSetNameCommon {
    TimeStepCommon=0,
    StartTimeCommon,
    TotalTimeCommon,
    OutputTimeIntervalCommon,
    NumberSetCommon
  };

  enum PropagatorParameterNameCommon {
    DeltaTime=0,
    HalfDeltaTime,
    StartTime,
    NowTime,
    TotalTime,
    OutputInterval,
    CountOutput,
    CountStepInOneOutput,
    NumberParameterCommon
  };

}

#endif

