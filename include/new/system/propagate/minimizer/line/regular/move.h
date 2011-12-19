
#ifndef _System_Propagate_Minimizer_Line_Regular_Move_H_
#define _System_Propagate_Minimizer_Line_Regular_Move_H_

#include "system/propagate/interface.h"
#include "system/propagate/minimizer/line/regular/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _MoveMinLineRegularShift(SysPropagate<T,VT,SCT>& SE) {}

}

#include "system/content/with-egv/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _MoveMinLineRegularShift(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    T step=*reinterpret_cast<T*>(SE.Param[PtrMinLineRegularStep].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      shift(SE.grpContent[i].X(),step,SE.grpContent[i].Velocity());
  }

}

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveMinLineRegularShift(SysPropagate<T,VT,SCT>& SE) {
    _MoveMinLineRegularShift(SE);
  }

}

#endif

