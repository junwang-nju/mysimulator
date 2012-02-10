
#ifndef _Dynamics_Canonical_Langevin_Base_Data_Link_H_
#define _Dynamics_Canonical_Langevin_Base_Data_Link_H_

#include "dynamics/canonical/langevin/base/data/interface.h"
#include "system/propagate/interface.h"
#include "system/property/mass-method-name.h"
#include "system/property/friction-method-name.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"

#define NAME(W,U)   W##LgVVerlet##U
#define DName(U)    NAME(Dat,U)
#define MName(U)    NAME(Mod,U)

#define _LinkArray(U,obj,X) \
  if(!IsSameSize(obj,X))  imprint(obj,X);\
  P[DName(U)].ptr[0]=reinterpret_cast<void*>(&(obj));

namespace mysimulator {

  template <typename T, typename<typename> class VT, typename RT,
            template<typename,template<typename>class> class SCT>
  void _link(DynamicsCanonicalLangevinBaseData<T,VT,RT>& D,
             SysPropagate<T,VT,SCT>& SE, const VT<T>& X) {
    assert(IsValid(SE)&&IsValid(X));
    Unique64Bit *P=SE.Param.start;
    assert(SE.Method==SysLangevinVelVerlet);
    MassMethodName MMN=static_cast<MassMethodName>(P[MName(Mass)].u[0]);
    FrictionMethodName FMN=
        static_cast<FrictionMethodName>(P[MName(Friction)].u[0]);
    _LinkArray(RandVector,D.RandV,X)
    P[DName(GaussRNG)].ptr[0]=reinterpret_cast<void*>(&(D.rng));
    if(FMN==ArrayFriction)  { _LinkArray(Friction,D.Friction,X) }
    if((MMN==ArrayMass)||(FMN==ArrayFriction)) {
      _LinkArray(RandSize,D.RandSize,X)
    }
  }

}

#undef _LinkArray

#undef MName
#undef DName
#undef NAME

#endif

