
#ifndef _Propagator_Set_Common_H_
#define _Propagator_Set_Common_H_

#include "propagator-parameter-name-common.h"

namespace std {

  void SetTimeStep(VectorBase<PropagatorDataElementType>& GPrm,
                   const void* pdt) {
    GPrm[DeltaTime]=*reinterpret_cast<const double*>(pdt);
    GPrm[HalfDeltaTime]=0.5*GPrm[DeltaTime].d;
  }

  void SetStartTime(VectorBase<PropagatorDataElementType>& GPrm,
                    const void *pst) {
    GPrm[StartTime]=*reinterpret_cast<const double*>(pst);
  }

  void SetTotalTime(VectorBase<PropagatorDataElementType>& GPrm,
                    const void* ptt) {
    GPrm[TotalTime]=*reinterpret_cast<const double*>(ptt);
  }

  void SetOutputInterval(VectorBase<PropagatorDataElementType>& GPrm,
                         const void* podt) {
    GPrm[OutputInterval]=*reinterpret_cast<const double*>(podt);
  }

  typedef void (*GSetFuncType)(
      VectorBase<PropagatorDataElementType>&, const void*);

  void AssignCommonSet4Propagator(VectorBase<GSetFuncType>& vSet) {
    assert(vSet.size()>=NumberSetCommon);
    vSet[TimeStepInCommon]=SetTimeStep;
    vSet[StartTimeInCommon]=SetStartTime;
    vSet[TotalTimeInCommon]=SetTotalTime;
    vSet[OutputTimeIntervalInCommon]=SetOutputInterval;
  }

}

#endif

