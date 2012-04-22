
#ifndef _System_Propagator_ToBeDetermined_Init_H_
#define _System_Propagator_ToBeDetermined_Init_H_

#include "system/propagator/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void InitTBD(SystemPropagator<T,CT>&) {}

}

#endif

