
#ifndef _System_Content_Data_E_Copy_H_
#define _System_Content_Data_E_Copy_H_

#include "system/content/data/e/interface.h"
#include "object/copy.h"

namespace mysimulator {

  template <typename T>
  void copy(SysContentDataE<T>& D, const SysContentDataE<T>& cD) {
    assert(IsValid(S)&&IsValid(cD));
    copy(D.Energy,cD.Energy);
  }

}

#endif

