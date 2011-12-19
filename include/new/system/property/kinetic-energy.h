
#ifndef _System_Property_KineticEnergy_H_
#define _System_Property_KineticEnergy_H_

#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/update-name.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/propagate/vverlet/langevin/update-name.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"

#define CName(U,Cond)  Calc##Cond##VVerlet##U
#define VName(U,Cond)  Val##Cond##VVerlet##U

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  T KineticEnergy(SysPropagate<T,VT,SCT>& SE) {
    T ke=0;
    switch(SE.Method) {
      case SysConstEVelVerlet:
        SE.update(CName(VSQ,CE));
        SE.update(CName(KE,CE));
        copy(ke,SE.Param[VName(KineticEnergy,CE)]);
        break;
      case SysLangevinVelVerlet:
        SE.update(CName(VSQ,Lg));
        SE.update(CName(KE,Lg));
        copy(ke,SE.Param[VName(KineticEnergy,Lg)]);
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

