
#ifndef _Propagator_Set_Common_H_
#define _Propagator_Set_Common_H_

#include "propagator-parameter-name-common.h"
#include "unique-parameter.h"

namespace std {

  void SetTimeStep(UniqueParameter* GPrm, const void* pdt) {
    GPrm[DeltaTime]=*reinterpret_cast<const double*>(pdt);
    GPrm[HalfDeltaTime]=0.5*GPrm[DeltaTime].d;
  }

  void SetStartTime(UniqueParameter* GPrm, const void* pst) {
    GPrm[StartTime]=*reinterpret_cast<const double*>(pst);
  }

  void SetTotalTime(UniqueParameter* GPrm, const void* ptt) {
    GPrm[TotalTime]=*reinterpret_cast<const double*>(ptt);
  }

  void SetOutputInterval(UniqueParameter* GPrm, const void* poi) {
    GPrm[OutputInterval]=*reinterpret_cast<const double*>(poi);
  }

  typedef void (*GSetFuncType4Propagator)(UniqueParameter*,const void*);
  void AssignCommonSet4Propagator(GSetFuncType4Propagator* vSet) {
    vSet[TimeStepCommon]=SetTimeStep;
    vSet[StartTimeCommon]=SetStartTime;
    vSet[TotalTimeCommon]=SetTotalTime;
    vSet[OutputTimeIntervalCommon]=SetOutputInterval;
  }

}

#endif

