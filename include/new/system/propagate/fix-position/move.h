
#ifndef _System_Propagate_FixPosition_Move_H_
#define _System_Propagate_FixPosition_Move_H_

#include "system/propagate/interface.h"
#include "system/propagate/fix-position/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveFixPosNoMove(SysPropagate<T,VT,SCT>& SE) {}

}

#endif

