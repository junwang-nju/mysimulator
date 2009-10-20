
#ifndef _Propagator_Common_Index_H_
#define _Propagator_Common_Index_H_

namespace std {

  enum PropagatorCommonType {
    BasicCommon=0,
    NumberCommonParam
  };

  enum BasicCommonType {
    DeltaTime=0,
    HalfDeltaTime,
    StartTime,
    NowTime,
    TotalTime,
    OutputInterval,
    CountOutput,
    CountStepInOne,
    NumberBasicCommon
  };

  enum SetCommonType {
    SetCmnTimeStep=0,
    SetCmnStartTime,
    SetCmnTotalTime,
    SetCmnOutputInterval,
    NumberSetCommon
  };

}

#endif

