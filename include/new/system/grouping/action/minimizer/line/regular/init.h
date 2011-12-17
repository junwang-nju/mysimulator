
#ifndef _System_Grouping_Action_Minimizer_Line_Regular_Init_H_
#define _System_Grouping_Action_Minimizer_Line_Regular_Init_H_

#include "system/grouping/action/minimizer/line/regular/update.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void InitMinimizerLineRegular(
      SCT<T,VT>& SC,SysInteraction<IDT,PT,GT,T>& SI,
      SysGrouping<T,IDT,PT,GT,VT,SCT>& SG) {}

}

#endif

