
#ifndef _System_Property_KineticEnergy_H_
#define _System_Property_KineticEnergy_H_

#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/update-name.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/propagate/vverlet/langevin/update-name.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"

#define CName(Cond)  Calc##Cond##VVerletKE
#define VName(Cond)  Val##Cond##VVerletKineticEnergy

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  T KineticEnergy(SysPropagate<T,VT,SCT>& SE) {
    T ke=0;
    switch(SE.Method) {
      case SysConstEVelVerlet:
        SE.update(CName(CE));
        copy(ke,SE.Param[VName(CE)]);
        break;
      case SysLangevinVelVerlet:
        SE.update(CName(Lg));
        copy(ke,SE.Param[VName(Lg)]);
        break;
      case SysBerendsenVelVerlet:
        SE.update(CName(Bs));
        copy(ke,SE.Param[VName(Bs)]);
        break;
      default:
        Error("This Type of Propagator Has No Kinetic Energy!");
    }
    return ke;
  }

}

#undef VName
#undef CName

#endif

