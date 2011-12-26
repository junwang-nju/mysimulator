
#ifndef _Dynamics_Output_Energy_Bind_H_
#define _Dynamics_Output_Energy_Bind_H_

#include "dynamics/output/energy/interface.h"
#include "dynamics/micro-canonical/specification.h"
#include "object/refer.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT, typename OST,
            template<typename,template<typename>class> class SCT>
  void bindOutput(
    Dynamics<MicroCanonical,T,VT,DynOutputEnergy<OST,T,IDT,PT,GT,VT,SCT> >& D,
    System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(S));
    assert(IsMatch(D,S));
    refer(D.Output.S,S);
    for(unsigned int i=0;i<S.Propagates.size;++i) {
      switch(S.Propagates[i].Param[CEVVerletMassMode].u[0]) {
        case GlobalMass:
          if(D.Output.gVelocitySQ.size<S.Propagates.size)
            allocate(D.Output.gVelocitySQ,S.Propagates.size);
          S.Propagates[i].Param[CEVVerletVelocitySQData].ptr[0]=
            reinterpret_cast<void*>(&(D.Output.gVelocitySQ[i]));
          break;
        case ArrayMass:
          if(!IsSameSize(D.Output.vVelocitySQ,S.Content().X()))
            imprint(D.Output.vVelocitySQ,S.Content().X());
          S.Propagates[i].Param[CEVVerletVelocitySQData].ptr[0]=
            reinterpret_cast<void*>(&(D.Output.vVelocitySQ));
          break;
        default:
          Error("Unknown Mass Mode!");
      }
    }
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT, typename OST,
            template<typename,template<typename>class> class SCT>
  void unbindOutput(
    Dynamics<MicroCanonical,T,VT,DynOutputEnergy<OST,T,IDT,PT,GT,VT,SCT> >& D,
    System<T,IDT,PT,GT,VT,SCT>& S) { release(D.Output.S); }

}

#endif

