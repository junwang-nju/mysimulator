
#ifndef _System_Grouping_Action_Minimizer_Line_Regular_Move_H_
#define _System_Grouping_Action_Minimizer_Line_Regular_Move_H_

#include "system/grouping/interface.h"
#include "system/content/with-egv/interface.h"
#include "system/grouping/action/minimizer/line/regular/parameter-name.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void EvoluteMinimizerLineRegular(
      SCT<T,VT>& SC, SysInteraction<IDT,PT,GT,T>&,
      SysGrouping<T,IDT,PT,GT,VT,SCT>& SG) {
    Error("Improper System Content Type!");
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void EvoluteMinimizerLineRegular(
      SysContentWithEGV<T,VT>& SC, SysInteraction<IDT,PT,GT,T>&,
      SysGrouping<T,IDT,PT,GT,VT,SysContentWithEGV>& SG) {
    assert(IsValid(SC)&&IsValid(SG));
    T step=*reinterpret_cast<T*>(SG.Param[MinLineRegularStep].ptr[0]);
    for(unsigned int i=0;i<SG.grpContent.size;++i)
      shift(SG.grpContent[i].X(),step,SG.grpContent[i].Velocity());
  }

}

#endif

