
#ifndef _VelocityVerlet_Move_H_
#define _VelocityVerlet_Move_H_

#include "data/propagator/propagator.h"
#include "data/name/propagator-vverlet.h"
#include "data/name/subsys-propagator-vverlet.h"

namespace std {

  template <typename T, typename ParameterType,
            template <typename,template<typename>class,typename> class IType,
            template <typename> class DBuffer, typename GeomType>
  void VVerletStep(Propagator<T>& P,
                   IType<T,DBuffer,GeomType>& F, ParameterType& pmx) {
    P[NowStepID].u++;
    typedef void (*sMoveFunc)(subsysPropagator<T>&);
    for(unsigned int i=0;i<P.sysPg.size;++i)
      if(P[NowStepID].u==P.sysPg[i][PropagateTrigger].u)
        reinterpret_cast<sMoveFunc>(P.sysPg[i][VVerletMove_BeforeG].ptr)(
            P.sysPg[i]);
    F.B.renew();
    update(pmx,P.X.structure,F.Geo);
    for(unsigned int i=0;i<P.G.nunit;++i)   copy(P.G[i],0.);
    CalcInteraction(F,P.X,pmx,P.G);
    for(unsigned int i=0;i<P.sysPg.size;++i)
      if(P[NowStepID].u==P.sysPg[i][PropagateTrigger].u) {
        reinterpret_cast<sMoveFunc>(P.sysPg[i][VVerletMove_AfterG].ptr)(
            P.sysPg[i]);
        P.sysPg[i][PropagateTrigger].u+=P.sysPg[i][PropagateTriggerStep].u;
      }
  }

}

#endif
