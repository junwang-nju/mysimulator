
#ifndef _System_Propagate_Allocate_H_
#define _System_Propagate_Allocate_H_

#include "system/propagate/interface.h"

#include "system/propagate/fix-position/move-name.h"
#include "system/propagate/fix-position/update-name.h"
#include "system/propagate/fix-position/init.h"
#include "system/propagate/fix-position/move.h"
#include "system/propagate/fix-position/update.h"

#include "system/propagate/minimizer/line/regular/move-name.h"
#include "system/propagate/minimizer/line/regular/update-name.h"
#include "system/propagate/minimizer/line/regular/init.h"
#include "system/propagate/minimizer/line/regular/move.h"
#include "system/propagate/minimizer/line/regular/update.h"

#include "system/propagate/to-be-determined/move-name.h"
#include "system/propagate/to-be-determined/update-name.h"
#include "system/propagate/to-be-determined/init.h"
#include "system/propagate/to-be-determined/move.h"
#include "system/propagate/to-be-determined/update.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void allocate(SysPropagate<T,VT,SCT>& SE,
                const SystemPropagateMethodName& EN) {
    release(SE);
    SE.Method=EN;
    switch(SE.Method) {
      case SysFixPosition:
        SE.initfunc=InitFixPosition<T,VT,SCT>;
        allocate(SE.evfunc,NumberMoveFixPosition);
        SE.evfunc[FixPosNoMove]=MoveFixPosNoMove<T,VT,SCT>;
        break;
      case SysMinimizerLineRegular:
        SE.initfunc=InitMinimizerLineRegular<T,VT,SCT>;
        allocate(SE.evfunc,NumberMoveMinimizerLineRegular);
        SE.evfunc[MinLineRegularShift]=MoveMinLineRegularShift<T,VT,SCT>;
        allocate(SE.Param,NumberParameterMinimizerLineRegular);
        break;
      case SysToBeDetermined:
        SE.initfunc=InitToBeDetermined<T,VT,SCT>;
        allocate(SE.evfunc,NumberMoveToBeDetermined);
        SE.evfunc[ToBeDeterminedNoMove]=MoveToBeDeterminedNoMove;
        break;
      default:
        Error("Unknown Method for System Evolution!");
    }
  }

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void allocate(SysPropagate<T,VT,SCT>& SE,
                const SystemPropagateMethodName& GM,const unsigned int& n) {
    allocate(SE,GM);
    allocate(SE.MerIDRange,n);
    allocate(SE.grpContent,n);
  }

}

#endif

