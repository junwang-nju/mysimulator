
#ifndef _Dynamics_Base_Data_Link_H_
#define _Dynamics_Base_Data_Link_H_

#include "dynamics/base/data/interface.h"
#include "system/propagate/interface.h"
#include "system/property/mass-method-name.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"
#include "system/propagate/vverlet/berendsen/parameter-name.h"

#define NAME(W,M,U)   W##M##U
#define PName(M,U)    NAME(Ptr,M,U)
#define MName(M,U)    NAME(Mod,M,U)
#define DName(M,U)    NAME(Dat,M,U)

#define _LinkElement(M,U,obj)   P[PName(M,U)].ptr[0]=&(obj);
#define _LinkArray(M,U,obj,X) \
  if(!IsSameSize(obj,X))  imprint(obj,X);\
  P[DName(M,U)].ptr[0]=reinterpret_cast<void*>(&(obj));

#define _LINK(M,X) \
  _LinkElement(M,TimeStep,D.TimeStep) \
  if(P[MName(M,Mass)].u[0]==ArrayMass) { _LinkArray(M,Mass,D.Mass,X) }

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _link(DynamicsBaseData<T,VT>& D, SysPropagate<T,VT,SCT>& SE,
             const VT<T>& X) {
    assert(IsValid(SE)&&IsValid(X));
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
        Error("Propagate Method Does Not fit Dynamics!");
    }
  }

}

#undef _LINK

#undef _LinkArray
#undef _LinkElement

#undef DName
#undef MName
#undef PName
#undef NAME

#include "system/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            typename DynamicsDataType>
  void link(DynamicsDataType& D, System<T,IDT,PT,GT,VT,SCT>& S) {
    assert(IsValid(S));
    for(unsigned int i=0;i<S.Propagates.size;++i)
      _link(D,S.Propagates[i],S.Content().X());
  }

}

#endif

