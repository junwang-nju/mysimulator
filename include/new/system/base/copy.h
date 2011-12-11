
#ifndef _System_Base_Copy_H_
#define _System_Base_Copy_H_

#include "system/base/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class SpaceType>
  void copy(SystemBase<T,SpaceType>& S, const SystemBase<T,SpaceType>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    copy(S.X,cS.X);
  }

}

#endif

