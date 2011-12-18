
#ifndef _System_Grouping_Allocate_H_
#define _System_Grouping_Allocate_H_

#include "array/1d/allocate.h"

#include "system/grouping/action/fix-position/move.h"
#include "system/grouping/action/fix-position/move-name.h"
#include "system/grouping/action/fix-position/init.h"
#include "system/grouping/action/fix-position/update.h"
#include "system/grouping/action/fix-position/update-name.h"

#include "system/grouping/action/minimizer/line/regular/move.h"
#include "system/grouping/action/minimizer/line/regular/move-name.h"
#include "system/grouping/action/minimizer/line/regular/init.h"
#include "system/grouping/action/minimizer/line/regular/update.h"
#include "system/grouping/action/minimizer/line/regular/update-name.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void allocate(SysGrouping<T,IDT,PT,GT,VT,SCT>& SG,
                const SystemGroupingMethodName& GM) {
    release(SG);
    SG.Method=GM;
    switch(SG.Method) {
      case SystemFixPosition:
        allocate(SG.evfunc,NumEvoluteFixPositionName);
        SG.evfunc[FixPositionNoMove]=
          EvoluteFixPositionNoMove<T,IDT,PT,GT,VT,SCT>;
        SG.inifunc=InitFixPosition<T,IDT,PT,GT,VT,SCT>;
        break;
      case SystemMinimizerLineRegular:
        allocate(SG.Param,NumParameterMinimizerLineRegularName);
        allocate(SG.evfunc,NumEvoluteMinimizerLineRegularName);
        SG.evfunc[MinimizerLineRegularShift]=
          EvoluteMinimizerLineRegularShift<T,IDT,PT,GT,VT>;
        SG.inifunc=InitMinimizerLineRegular<T,IDT,PT,GT,VT,SCT>;
        break;
      default:
        Error("Unknown Method for System Grouping!");
    }
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void allocate(SysGrouping<T,IDT,PT,GT,VT,SCT>& SG,
                const SystemGroupingMethodName& GM, const unsigned int& n) {
    allocate(SG,GM);
    allocate(SG.MerIDRange,n);
    allocate(SG.grpContent,n);
  }

}

#endif

