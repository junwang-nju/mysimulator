
#ifndef _System_Content_Data_Gradient_Nullify_H_
#define _System_Content_Data_Gradient_Nullify_H_

#include "system/content/data/g/interface.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T, template <typename> class VT>
  void nullify(SysContentDataG<T,VT>& D) {
    assert(IsValid(D));
    fill(D.Gradient(),cZero);
  }

}

#endif

