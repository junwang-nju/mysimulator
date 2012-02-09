
#ifndef _Dynamics_Algorithm_VelocityVerlet_Data_Link_H_
#define _Dynamics_Algorithm_VelocityVerlet_Data_Link_H_

#include "dynamics/vverlet/data/interface.h"
#include "system/propagate/interface.h"
#include "system/property/mass-method-name.h"

#define NAME(W,M,U)   W##VVerlet##M##U
#define DName(M,U)    NAME(Dat,M,U)
#define MName(M,U)    NAME(Mod,M,U)

#define _LinkArray(M,U,obj,X) \
  if(!IsSameSize(obj,X))  imprint(obj,X);\
  P[DName(M,U)].ptr[0]=reinterpret_cast<void*>(&(obj));

#define _LINK(M,X) \
  if(P[MName(M,Mass)].ptr[0]==ArrayMass) { _LinkArray(M,NegHTIM,D.NegHTIM,X) }

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _link(DynamicsVVerletData<T,VT>& D, SysPropagate<T,VT,SCT>& SE,
             const VT<T>& X) {
    assert(IsValid(D)&&IsValid(SE)&&IsValid(X));
    Unique64Bit *P=SE.Param.start;
    switch(SE.Method) {
      case SysConstEVelVerlet:
        _LINK(CE,X)
        break;
      case SysLangevinVelVerlet:
        _LINK(Lg,X)
        break;
      case SysBerendsenVelVerlet:
        _LINK(Bs,X)
        break;
      default:
        Error("Propagate Method Does Not fit Dynamics!");
    }
  }

}

#undef _LINK
#undef _LinkArray
#undef MName
#undef DName
#undef NAME

#endif

