
#ifndef _System_Property_KineticEnergy_H_
#define _System_Property_KineticEnergy_H_

#include "system/propagate/interface.h"
#include "system/propagate/vverlet/const-e/update-name.h"
#include "system/propagate/vverlet/const-e/parameter-name.h"
#include "system/propagate/vverlet/langevin/update-name.h"
#include "system/propagate/vverlet/langevin/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  T KineticEnergy(SysPropagate<T,VT,SCT>& SE) {
    T ke=0;
    switch(SE.Method) {
      case SysConstEVelVerlet:
        SE.update(CEVVerletVSQCalc);
        SE.update(CEVVerletKECalc);
        copy(ke,SE.Param[CEVVerletKineticEnergy]);
        break;
      case SysLangevinVelVerlet:
        SE.update(LgVVerletVSQCalc);
        SE.update(LgVVerletKECalc);
        copy(ke,SE.Param[LgVVerletKineticEnergy]);
        break;
      default:
        Error("This Type of Propagator Has No Kinetic Energy!");
    }
    return ke;
  }

}

#endif

