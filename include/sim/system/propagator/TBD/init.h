
#ifndef _System_Propagator_TBD_Init_H_
#define _System_Propagator_TBD_Init_H_

#include "system/propagator/interface.h"
#include "system/propagator/TBD/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void InitTBD(SystemPropagator<T,CT>&,CT<T>&) {}

}

#endif

