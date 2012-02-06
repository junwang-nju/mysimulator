
#ifndef _Dynamics_Output_Energy_Bind_H_
#define _Dynamics_Output_Energy_Bind_H_

#include "dynamics/output/energy/interface.h"
#include "object/refer.h"
#include "dynamics/micro-canonical/specification.h"

#define DName(U)      DatCEVVerlet##U

#define _LinkArray(U,obj) \
  if(!IsSameSize(obj,S.Content().X()))  imprint(obj,S.Content().X());\
  S.Propagates[i].Param[DName(U)].ptr[0]=reinterpret_cast<void*>(&(obj));

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
      switch(S.Propagates[i].Param[ModCEVVerletMass].u[0]) {
        case GlobalMass:
          break;
        case ArrayMass:
          _LinkArray(VelocitySQ,D.Output.VelocitySQ)
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

#undef _LinkArray

#undef DName

#include "dynamics/langevin/specification.h"

#define _OLinkArray(name,obj) \
  if(!IsSameSize(obj,S.Content().X()))  imprint(obj,S.Content().X());\
  S.Propagates[i].Param[name].ptr[0]=reinterpret_cast<void*>(&(obj));

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT, typename OST,
            template<typename,template<typename>class> class SCT>
  void bindOutput(
    Dynamics<Langevin,T,VT,DynOutputEnergy<OST,T,IDT,PT,GT,VT,SCT> >& D,
    System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(S));
    assert(IsMatch(D,S));
    refer(D.Output.S,S);
    for(unsigned int i=0;i<S.Propagates.size;++i) {
      switch(S.Propagates[i].Param[LgVVerletMassMode].u[0]) {
        case GlobalMass:
          break;
        case ArrayMass:
          _OLinkArray(LgVVerletVelocitySQData,D.Output.vVelocitySQ)
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
      Dynamics<Langevin,T,VT,DynOutputEnergy<OST,T,IDT,PT,GT,VT,SCT> >& D,
      System<T,IDT,PT,GT,VT,SCT>& S) { release(D.Output.S); }

}

#undef _OLinkArray

#endif

