
#ifndef _System_Content_Base_Imprint_H_
#define _System_Content_Base_Imprint_H_

#include "system/content/base/interface.h"
#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentBase<T>& C, const SystemContentBase<T>& iC) {
    release(C);
    imprint(C.X,iC.X);
  }

}

#endif

