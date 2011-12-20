
#ifndef _System_Content_Data_Energy_Nullify_H_
#define _System_Content_Data_Energy_Nullify_H_

#include "system/content/data/e/interface.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T>
  void nullify(SysContentDataE<T>& D) {
    assert(IsValid(D));
    copy(D.Energy(),cZero);
  }

}

#endif

