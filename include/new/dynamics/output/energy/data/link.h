
#ifndef _Dynamics_Output_Energy_Data_Link_H_
#define _Dynamics_Output_Energy_Data_Link_H_

#include "dynamics/output/energy/interface.h"
#include "system/propagate/interface.h"
#include "system/property/mass-method-name.h"

#define NAME(W,M,U)   W##M##U
#define MName(M,U)    NAME(Mod,M,U)
#define DName(M,U)    NAME(Dat,M,U)

#define _LinkArray(M,U,obj,X) \
  if(!IsSameSize(obj,X))  imprint(obj,X);\
  P[DName(M,U)].ptr[0]=reinterpret_cast<void*>(&(obj));

#define _LINK(M,X) \
  if(P[MName(M,Mass)].u[0]==ArrayMass) { \
    _LinkArray(M,VelocitySQ,D.VelocitySQ,X) \
  }

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _link(DynamicsOutputEnergyData<T,IDT,PT,GT,VT,SCT>& D,
             SysPropagate<T,VT,SCT>& SE, const VT<T>& X) {
    assert(IsValid(D)&&IsValid(SE)&&IsValid(X));
    Unique64Bit *P=SE.Param.start;
    switch(SE.Method) {
      case SysConstEVelVerlet:
        _LINK(CEVVerlet,X)
        break;
      case SysLangevinVelVerlet:
        _LINK(LgVVerlet,X)
        break;
      case SysBerendsenVelVerlet:
        _LINK(BsVVerlet,X)
        break;
      default:
        Error("Propagate Mehtod Does Not fit Output of Dynamics!");
    }
  }

}

#undef _LINK
#undef _LinkArray

#undef DName
#undef MName
#undef NAME

#include "system/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void link(DynamicsOutputEnergyData<T,IDT,PT,GT,VT,SCT>& D,
            System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(D)&&IsValid(S));
    refer(D.S,S);
    for(unsigned int i=0;i<S.Propagates.size;++i)
      _link(D,S.Propagates[i],S.Content().X());
  }

}

#endif

