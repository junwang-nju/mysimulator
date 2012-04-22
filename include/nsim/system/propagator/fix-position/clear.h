
#ifndef _System_Propagator_FixPosition_Clear_H_
#define _System_Propagator_FixPosition_Clear_H_

#include "system/propagator/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class CT>
  void ClearFixPosition(SystemPropagator<T,CT>&) {}

}

#endif

