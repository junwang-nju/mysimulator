
#ifndef _System_Propagator_ToBeDetermined_Move_H_
#define _System_Propagator_ToBeDetermined_Move_H_

#include "system/propagator/interface.h"

namespace mysimulator {

  template<typename T, template<typename> class CT>
  void MoveTBDNoMove(SystemPropagator<T,CT>& P) {
    fprintf(stderr,"No Move Assigned!\n");
  }

}

#endif

