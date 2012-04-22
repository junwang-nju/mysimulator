
#ifndef _System_Propagator_FixPosition_Move_H_
#define _System_Propagator_FixPosition_Move_H_

#include "system/propagator/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void MoveFixPositionNoMove(SystemPropagator<T,CT>& P) {}

}

#endif

