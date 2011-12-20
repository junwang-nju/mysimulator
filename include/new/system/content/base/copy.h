
#ifndef _System_Content_Base_Copy_H_
#define _System_Content_Base_Copy_H_

#include "system/content/base/interface.h"
#include "object/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void copy(SysContentBase<T,VT>& S, const SysContentBase<T,VT>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    copy(S.X,cS.X);
  }

}

#endif

