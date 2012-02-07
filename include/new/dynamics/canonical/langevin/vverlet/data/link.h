
#ifndef _Dynamics_Canonical_Langevin_VelocityVerlet_Data_Link_H_
#define _Dynamics_Canonical_Langevin_VelocityVerlet_Data_Link_H_

#include "dynamics/canonical/langevin/vverlet/data/interface.h"
#include "system/propagate/interface.h"
#include "system/property/mass-method-name.h"
#include "system/property/friction-method-name.h"

#define NAME(W,U)   W##LgVVerlet##U
#define DName(U)    NAME(Dat,U)
#define MName(U)    NAME(Mod,U)

#define _LinkArray(U,obj,X) \
  if(!IsSameSize(obj,X))  imprint(obj,X);\
  P[DName(U)].ptr[0]=reinterpret_cast<void*>(&(obj));

namespace mysimulator {
  
  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _link(DynamicsCanonicalLangevinVVerletData<T,VT>& D,
             SysPropagate<T,VT,SCT>& SE, const VT<T>& X) {
    assert(IsValid(SE)&&IsValid(X));
    Unique64Bit *P=SE.Param.start;
    assert(SE.Method==SysLangevinVelVerlet);
    MassMethodName MMN=static_cast<MassMethodName>(P[MName(Mass)].u[0]);
    FrictionMethodName FMN=
        static_cast<FrictionMethodName>(P[MName(Friction)].u[0]);
    if((MMN==ArrayMass)||(FMN==ArrayFriction)) {
      _LinkArray(Fac1,D.Fac1,X)
      _LinkArray(Fac2,D.Fac2,X)
    }
  }

}

#undef _LinkArray
#undef DName
#undef MName
#undef NAME

#endif

