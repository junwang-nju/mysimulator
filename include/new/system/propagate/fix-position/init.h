
#ifndef _System_Propagate_FixPosition_Init_H_
#define _System_Propagate_FixPosition_Init_H_

#include "system/propagate/interface.h"
#include "system/propagate/fix-position/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _InitFixPosition(SysPropagate<T,VT,SCT>& SE) {}

}

#define _InitFunc(SCType) \
  template <typename T,template<typename> class VT> \
  void _InitFixPosition(SysPropagate<T,VT,SCType>& SE) {\
    assert(IsValid(SE));\
    for(unsigned int i=0;i<SE.grpContent.size;++i) \
      fill(SE.grpContent[i].Velocity(),cZero); \
  }

#include "system/content/with-v/interface.h"
#include "system/content/with-ev/interface.h"
#include "system/content/with-egv/interface.h"

namespace mysimulator {

  _InitFunc(SysContentWithV)
  _InitFunc(SysContentWithEV)
  _InitFunc(SysContentWithEGV)

}

#undef _InitFunc

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void InitFixPosition(SysPropagate<T,VT,SCT>& SE) { _InitFixPosition(SE); }

}

#endif

