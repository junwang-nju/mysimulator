
#ifndef _Propagator_Parameter_Update_Common_H_
#define _Propagator_Parameter_Update_Common_H_

#include "propagator/base/interface.h"
#include "propagator/base/parameter/common/name.h"
#include "propagator/subsystem/parameter/common/name.h"

namespace mysimulator {

  template <typename T>
  void UpdatePropagatorBaseCommon(PropagatorBase<T>& P) {
    T mstep;
    mstep=P.Sys[0].value(TimeStep);
    for(unsigned int i=1;i<P.Sys.size;++i)
      mstep=(mstep<P.Sys[i].value(TimeStep)?mstep:P.Sys[i].value(TimeStep));
    P.value(RunTimeStep)=mstep;
    T tmd;
    for(unsigned int i=0;i<P.Sys.size;++i) {
      tmd=P.Sys[i].value(TimeStep)/mstep;
      P.Sys[i].Data[MoveTrigInterval].u=static_cast<unsigned int>(tmd-0.5)+1;
      P.Sys[i].value(TimeStep)=P.Sys[i].Data[MoveTrigInterval].u*mstep;
    }
    for(unsigned int i=0;i<P.Sys.size;++i)    P.Sys[i].Update(P.Sys[i]);
    P.Data[NumberOutput].u=
      static_cast<unsigned int>(P.value(TotalTime)/P.value(OutputInterval)-0.5)
      +1;
    P.Data[NumberStepPerOutput].u=
      static_cast<unsigned int>(P.value(OutputInterval)/P.value(RunTimeStep)
          -0.5)+1;
    P.value(TotalTime)=P.Data[NumberOutput].u*P.value(OutputInterval);
    copy(P.data[NowTime],P.data[StartTime]);
    P.Data[NowStepID].u=0;
    for(unsigned int i=0;i<P.Sys.size;++i)
    for(unsigned int j=0;j<P.Sys[i].Mer.size;++j) {
      P.Sys[i].Mer[j].Data[XData].ptr=(&(P.X[P.ID[i][j]]));
      P.Sys[i].Mer[j].Data[VData].ptr=(&(P.V[P.ID[i][j]]));
      P.Sys[i].Mer[j].Data[GData].ptr=(&(P.G[P.ID[i][j]]));
      P.Sys[i].Mer[j].Data[MskData].ptr=(&(P.Msk[P.ID[i][j]]));
    }
  }

}

#endif

