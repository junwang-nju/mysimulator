
#ifndef _Dynamics_Canonical_Base_Data_Link_H_
#define _Dynamics_Canonical_Base_Data_Link_H_

#include "dynamics/canonical/base/data/interface.h"
#include "system/propagate/interface.h"

#define NAME(W,M,U)     W##M##U
#define PName(M,U)      NAME(Ptr,M,U)

#define _LinkElement(M,U,obj) \
  P[PName(M,U)].ptr[0]=reinterpret_cast<void*>(&(obj));

#define _LINK(M) \
  _LinkElement(M,Temperature,D.Temperature)

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _link(DynamicsCanonicalBaseData<T>& D, SysPropagate<T,VT,SCT>& SE,
             const VT<T>&) {
    assert(IsValid(SE));
    Unique64Bit *P=SE.Param.start;
    switch(SE.Method) {
      case SysLangevinVelVerlet:
        _LINK(LgVVerlet)
        break;
      case SysBerendsenVelVerlet:
        _LINK(BsVVerlet)
        break;
      default:
        Error("System Do Not Has This Data!");
    }
  }

}

#undef _LINK
#undef _LinkElement

#undef PName
#undef NAME

#endif

