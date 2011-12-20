
#ifndef _System_Propagate_ToBeDetermined_Move_H_
#define _System_Propagate_ToBeDetermined_Move_H_

#include "system/propagate/interface.h"
#include "system/propagate/to-be-determined/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveToBeDeterminedNoMove(SysPropagate<T,VT,SCT>& SE) {
    Error("No Move Assigned!");
  }

}

#endif

