
#ifndef _Propagator_Parameter_Name_Common_H_
#define _Propagator_Parameter_Name_Common_H_

namespace std {

  enum PropagatorParamNameCommon {
    DeltaTime=0,
    HalfDeltaTime,
    StartTime,
    NowTime,
    TotalTime,
    OutputInterval,
    CountOutput,
    CountStepInOne,
    NumberParamCommon
  };

  enum PropagatorSetNameCommon {
    TimeStepInCommon=0,
    StartTimeInCommon,
    TotalTimeInCommon,
    OutputTimeIntervalInCommon,
    NumberSetCommon
  };

}

#endif

