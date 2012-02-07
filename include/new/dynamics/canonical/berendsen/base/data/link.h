
#ifndef _Dynamics_Canonical_Berendsen_Base_Data_Link_H_
#define _Dynamics_Canonical_Berendsen_Base_Data_Link_H_

#include "dynamics/canonical/berendsen/base/data/interface.h"
#include "system/propagate/interface.h"
#include "system/property/mass-method-name.h"

#define NAME(W,U)     W##BsVVerlet##U
#define DName(U)      NAME(Dat,U)
#define MName(U)      NAME(Mod,U)
#define PName(U)      NAME(Ptr,U)

#define _LinkElement(U,obj) \
  P[PName(U)].ptr[0]=reinterpret_cast<void*>(&(obj));

#define _LinkArray(U,obj,X) \
  if(!IsSameSize(obj,X))  imprint(obj,X);\
  P[DName(U)].ptr[0]=reinterpret_cast<void*>(&(obj));

namespace mysimulator {

  template <typename T,template<typename>class VT,
            template<typename,template<typename>class> class SCT>
  void _link(DynamicsCanonicalBerendsenBaseData<T,VT>& D,
             SysPropagate<T,VT,SCT>& SE, const VT<T>& X) {
    assert(IsValid(SE)&&IsValid(X));
    Unique64Bit *P=SE.Param.start;
    assert(SE.Method==SysBerendsenVelVerlet);
    _LinkElement(RelaxTime,D.RelaxTime)
    if(P[MName(Mass)].u[0]==ArrayMass) { _LinkArray(VelocitySQ,D.VelocitySQ,X) }
  }

  template <typename T,template<typename>class VT,
            template<typename,template<typename>class> class SCT>
  void _link(DynamicsCanonicalBerendsenBaseData4EnergyOut<T>& D,
             SysPropagate<T,VT,SCT>& SE, const VT<T>& X) {
    assert(IsValid(SE)&&IsValid(X));
    Unique64Bit *P=SE.Param.start;
    assert(SE.Method==SysBerendsenVelVerlet);
    _LinkElement(RelaxTime,D.RelaxTime)
  }

}

#undef _LinkArray
#undef _LinkElement

#undef PName
#undef MName
#undef DName
#undef NAME

#endif

