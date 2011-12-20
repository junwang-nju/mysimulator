
#ifndef _System_Propagate_ToBeDetermined_Init_H_
#define _System_Propagate_ToBeDetermined_Init_H_

#include "system/propagate/interface.h"
#include "system/propagate/to-be-determined/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void InitToBeDetermined(SysPropagate<T,VT,SCT>& SE) {}

}

#endif
