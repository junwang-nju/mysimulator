
#ifndef _System_Content_Base_Copy_H_
#define _System_Content_Base_Copy_H_

#include "system/content/base/interface.h"
#include "object/copy.h"

namespace mysimulator {

  template <typename T,template<typename> class VecType>
  void copy(SysContentBase<T,VecType>& S, const SysContentBase<T,VecType>& rS) {
    assert(IsValid(S)&&IsValid(rS));
    copy(S.X,rS.X);
  }

}

#endif

