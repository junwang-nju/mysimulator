
#ifndef _Propagator_Move_VelocityVerlet_Step_H_
#define _Propagator_Move_VelocityVerlet_Step_H_

#include "propagator/interface.h"
#include "interaction/calc.h"
#include "propagator/parameter/vverlet/name.h"
#include "propagator/subsystem/parameter/vverlet/name.h"
#include "propagator/move/vverlet/name.h"
#include "list/fill.h"

namespace mysimulator {

  template <typename T, template<typename> class DBuffer, typename GeomType,
            typename IFType, typename IPType>
  void VelVerletStep(Propagator<T>& P,
                     InteractionKernel<IFType,DBuffer,GeomType>& K,
                     const IPType& Prm) {
    P.Data[NowStepID].u++;
    for(unsigned int i=0;i<P.Sys.size;++i)
      if(P[NowStepID].u==P.Sys[i].Data[MoveTrig])
        P.Sys[i].Move[BeforeG](P.Sys[i]);
    K.update();
    fill(P.G,cZero);
    Calc(K,P.X,Prm,P.G);
    for(unsigned int i=0;i<P.Sys.size;++i)
      if(P[NowStepID].u==P.Sys[i].Data[MoveTrig]) {
        P.Sys[i].Move[AfterG](P.Sys[i]);
        P.Sys[i].Data[MoveTrig].u+=P.Sys[i].Data[MoveTrigInterval].u;
      }
  }

}

#endif

