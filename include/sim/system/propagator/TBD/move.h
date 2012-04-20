
#ifndef _System_Propagator_TBD_Move_H_
#define _System_Propagator_TBD_Move_H_

#include "system/propagator/interface.h"
#include "system/propagator/TBD/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void MoveTBDNoMove(SystemPropagator<T,CT>&,CT<T>&) {
    sprintf(stderr,"No MOVE!\n");
  }

}

#endif

