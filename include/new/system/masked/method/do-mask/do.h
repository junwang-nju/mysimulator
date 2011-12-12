
#ifndef _System_Masked_Method_DoMask_Do_H_
#define _System_Masked_Method_DoMask_Do_H_

#include "system/masked/component/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class SpaceType>
  struct _SystemDoMaskApply {
    void Do(SpaceType<T>& V, const Mask4System<T,SpaceType>& M) {
      scale(V,M.Mask);
    }
  };

}

#endif

