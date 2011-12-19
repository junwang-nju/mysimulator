
#ifndef _System_Propagate_Allocate_H_
#define _System_Propagate_Allocate_H_

#include "system/propagate/interface.h"

#include "system/propagate/fix-position/move-name.h"
#include "system/propagate/fix-position/update-name.h"
#include "system/propagate/fix-position/init.h"
#include "system/propagate/fix-position/move.h"
#include "system/propagate/fix-position/update.h"
#include "system/propagate/fix-position/clear.h"

#include "system/propagate/minimizer/line/regular/move-name.h"
#include "system/propagate/minimizer/line/regular/update-name.h"
#include "system/propagate/minimizer/line/regular/init.h"
#include "system/propagate/minimizer/line/regular/move.h"
#include "system/propagate/minimizer/line/regular/update.h"
#include "system/propagate/minimizer/line/regular/clear.h"

#include "system/propagate/to-be-determined/move-name.h"
#include "system/propagate/to-be-determined/update-name.h"
#include "system/propagate/to-be-determined/init.h"
#include "system/propagate/to-be-determined/move.h"
#include "system/propagate/to-be-determined/update.h"
#include "system/propagate/to-be-determined/clear.h"

#include "system/propagate/vverlet/const-e/move-name.h"
#include "system/propagate/vverlet/const-e/update-name.h"
#include "system/propagate/vverlet/const-e/init.h"
#include "system/propagate/vverlet/const-e/move.h"
#include "system/propagate/vverlet/const-e/update.h"
#include "system/propagate/vverlet/const-e/clear.h"

#include "system/propagate/vverlet/langevin/move-name.h"
#include "system/propagate/vverlet/langevin/update-name.h"
#include "system/propagate/vverlet/langevin/init.h"
#include "system/propagate/vverlet/langevin/move.h"
#include "system/propagate/vverlet/langevin/update.h"
#include "system/propagate/vverlet/langevin/clear.h"

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
        SE.clrfunc=ClearFixPosition<T,VT,SCT>;
        allocate(SE.evfunc,NumberMoveFixPosition);
        SE.evfunc[FixPosNoMove]=MoveFixPosNoMove<T,VT,SCT>;
        break;
      case SysMinimizerLineRegular:
        SE.initfunc=InitMinimizerLineRegular<T,VT,SCT>;
        SE.clrfunc=ClearMinimizerLineRegular<T,VT,SCT>;
        allocate(SE.evfunc,NumberMoveMinimizerLineRegular);
        SE.evfunc[MinLineRegularShift]=MoveMinLineRegularShift<T,VT,SCT>;
        allocate(SE.Param,NumberParameterMinimizerLineRegular);
        break;
      case SysToBeDetermined:
        SE.initfunc=InitToBeDetermined<T,VT,SCT>;
        SE.clrfunc=ClearToBeDetermined<T,VT,SCT>;
        allocate(SE.evfunc,NumberMoveToBeDetermined);
        SE.evfunc[ToBeDeterminedNoMove]=MoveToBeDeterminedNoMove;
        break;
      case SysConstEVelVerlet:
        SE.initfunc=InitCEVVerlet<T,VT,SCT>;
        SE.clrfunc=ClearCEVVerlet<T,VT,SCT>;
        allocate(SE.evfunc,NumberMoveConstEVelVerlet);
        SE.evfunc[CEVVerletBeforeG]=MoveCEVVerletBeforeG<T,VT,SCT>;
        SE.evfunc[CEVVerletAfterG]=MoveCEVVerletAfterG<T,VT,SCT>;
        allocate(SE.updfunc,NumberUpdateConstEVelVerlet);
        SE.updfunc[CalcCEVVerletHTIM]=UpdateCEVVerletHTIM<T,VT,SCT>;
        SE.updfunc[CalcCEVVerletVSQ]=UpdateCEVVerletVelocitySQ<T,VT,SCT>;
        SE.updfunc[CalcCEVVerletKE]=UpdateCEVVerletKEnergy<T,VT,SCT>;
        allocate(SE.Param,NumberParameterConstEVelVerlet);
        break;
      case SysLangevinVelVerlet:
        SE.initfunc=InitLgVVerlet<T,VT,SCT>;
        SE.clrfunc=ClearLgVVerlet<T,VT,SCT>;
        allocate(SE.evfunc,NumberMoveLangevinVelVerlet);
        SE.evfunc[LgVVerletBeforeG]=MoveLgVVerletBeforeG<T,VT,SCT>;
        SE.evfunc[LgVVerletAfterG]=MoveLgVVerletAfterG<T,VT,SCT>;
        allocate(SE.updfunc,NumberUpdateLangevinVelVerlet);
        SE.updfunc[CalcLgVVerletNegHTIM]=UpdateLgVVerletNegHTIM<T,VT,SCT>;
        SE.updfunc[CalcLgVVerletRandSize]=UpdateLgVVerletRandSize<T,VT,SCT>;
        SE.updfunc[CalcLgVVerletFac]=UpdateLgVVerletFac<T,VT,SCT>;
        SE.updfunc[CalcLgVVerletVSQ]=UpdateLgVVerletVelocitySQ<T,VT,SCT>;
        SE.updfunc[CalcLgVVerletKE]=UpdateLgVVerletKEnergy<T,VT,SCT>;
        allocate(SE.Param,NumberParameterLangevinVelVerlet);
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

