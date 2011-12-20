
#ifndef _System_Propagate_Minimizer_Line_Regular_Init_H_
#define _System_Propagate_Minimizer_Line_Regular_Init_H_

#include "system/propagate/minimizer/line/regular/parameter-name.h"
#include "system/propagate/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void InitMinimizerLineRegular(SysPropagate<T,VT,SCT>& SE) {}

}

#endif

