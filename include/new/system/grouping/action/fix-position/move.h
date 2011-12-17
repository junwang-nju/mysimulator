
#ifndef _System_Grouping_Action_FixPosition_Move_H_
#define _System_Grouping_Action_FixPosition_Move_H_

#include "system/grouping/interface.h"
#include "system/grouping/action/fix-position/parameter-name.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename> class> class SCT>
  void EvoluteFixPosition(SCT<T,VT>& S, SysInteraction<IDT,PT,GT,T>& SI,
                          SysGrouping<T,IDT,PT,GT,VT,SCT>& SG) {}

}

#endif

