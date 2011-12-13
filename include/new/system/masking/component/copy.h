
#ifndef _System_Masking_Component_Copy_H_
#define _System_Masking_Component_Copy_H_

#include "system/masking/component/interface.h"

namespace mysimulator {

  template <typename T1, typename T2, template<typename> class SpaceType>
  void copy(Mask4System<T1,SpaceType>& M, const Mask4System<T2,SpaceType>& cM) {
    assert(IsValid(M)&&IsValid(cM));
    copy(M.iMask,cM.iMask);
    copy(M.Mask,M.iMask);
  }

}

#endif

