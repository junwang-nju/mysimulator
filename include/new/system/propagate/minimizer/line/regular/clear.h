
#ifndef _System_Propagate_Minimizer_Line_Regular_Clear_H_
#define _System_Propagate_Minimizer_Line_Regular_Clear_H_

#include "system/propagate/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void ClearMinimizerLineRegular(SysPropagate<T,VT,SCT>&) {}

}

#endif

