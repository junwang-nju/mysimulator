
#ifndef _Build_Parameter_Propagator_Base_H_
#define _Build_Parameter_Propagator_Base_H_

#include "data/basic/unique-parameter.h"
#include "data/name/propagator-base.h"
#include "data/propagator/propagator.h"
#include "data/name/subsys-propagator-base.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorBase(Propagator<T>& P) {
    T mTStep,tmvalue;
    mTStep=static_cast<UniqueParameter&>(P.sysPg[0][TimeStep]).value<T>();
    for(unsigned int i=1;i<P.sysPg.size;++i) {
      tmvalue=static_cast<UniqueParameter&>(P.sysPg[i][TimeStep]).value<T>();
      mTStep=(mTStep<tmvalue?mTStep:tmvalue);
    }
    copy(P[RunTimeStep],mTStep);
    for(unsigned int i=0;i<P.sysPg.size;++i) {
      tmvalue=static_cast<UniqueParameter&>(P.sysPg[i][TimeStep]).value<T>();
      tmvalue/=mTStep;
      P.sysPg[i][PropagateTriggerStep].u=
        static_cast<unsigned int>(tmvalue-0.5)+1;
      copy(P.sysPg[i][TimeStep],P.sysPg[i][PropagateTriggerStep].u*mTStep);
    }
    typedef void (*sBuildFunc)(subsysPropagator<T>&);
    for(unsigned int i=0;i<P.sysPg.size;++i)
      reinterpret_cast<sBuildFunc>(P.sysPg[i][subsysPgBuild].ptr)(P.sysPg[i]);
    P[NumberOutput].u=
      static_cast<unsigned int>(
          static_cast<UniqueParameter&>(P[TotalTime]).value<T>()/
          static_cast<UniqueParameter&>(P[OutputInterval]).value<T>()-0.5)+1;
    P[NumberStepInOneOutput].u=
      static_cast<unsigned int>(
          static_cast<UniqueParameter&>(P[OutputInterval]).value<T>()/
          static_cast<UniqueParameter&>(P[RunTimeStep]).value<T>()-0.5)+1;
    copy(P[TotalTime],
         P[NumberOutput].u*
         static_cast<UniqueParameter&>(P[OutputInterval]).value<T>());
    copy(P[NowTime],P[StartTime]);
    P[NowStepID].u=0;
  }

}

#endif
