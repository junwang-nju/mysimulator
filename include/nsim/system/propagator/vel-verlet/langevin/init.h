
#ifndef _System_Propagator_VelVerlet_Langevin_Init_H_
#define _System_Propagator_VelVerlet_Langevin_Init_H_

#include "system/propagator/interface.h"
#include "system/propagator/vel-verlet/langevin/parameter-name.h"
#include "system/property/mass-method-name.h"
#include "system/property/friction-method-name.h"

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void InitVelVerletLangevin(SystemPropagator<T,CT>& P) {
  }

}

#endif

