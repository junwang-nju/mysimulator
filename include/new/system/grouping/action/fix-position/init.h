
#ifndef _System_Grouping_Action_FixPosition_Init_H_
#define _System_Grouping_Action_FixPosition_Init_H_

#include "system/grouping/interface.h"
#include "system/grouping/action/fix-position/parameter-name.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename> class> class SCT>
  void InitFixPosition(SCT<T,VT>&, SysInteraction<IDT,PT,GT,T>&,
                       SysGrouping<T,IDT,PT,GT,VT,SCT>& SG) {}

}

#include "system/content/with-v/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void InitFixPosition(SysContentWithV<T,VT>&,
                       SysInteraction<IDT,PT,GT,T>&,
                       SysGrouping<T,IDT,PT,GT,VT,SysContentWithV>& SG) {
    assert(IsValid(SG));
    for(unsigned int i=0;i<SG.grpContent.size;++i)
      fill(SG.grpContent[i].Velocity(),cZero);
  }

}

#include "system/content/with-ev/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void InitFixPosition(SysContentWithEV<T,VT>& SC,
                       SysInteraction<IDT,PT,GT,T>&,
                       SysGrouping<T,IDT,PT,GT,VT,SysContentWithEV>& SG) {
    assert(IsValid(SG));
    for(unsigned int i=0;i<SG.grpContent.size;++i)
      fill(SG.grpContent[i].Velocity(),cZero);
  }

}

#include "system/content/with-egv/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT>
  void InitFixPosition(SysContentWithEGV<T,VT>& SC,
                       SysInteraction<IDT,PT,GT,T>&,
                       SysGrouping<T,IDT,PT,GT,VT,SysContentWithEGV>& SG) {
    assert(IsValid(SG));
    for(unsigned int i=0;i<SG.grpContent.size;++i)
      fill(SG.grpContent[i].Velocity(),cZero);
  }

}

#endif

