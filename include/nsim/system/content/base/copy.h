
#ifndef _System_Content_Base_Copy_H_
#define _System_Content_Base_Copy_H_

#include "system/content/base/interface.h"
#include "array/2d/copy.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentBase<T>& C,const SystemContentBase<T>& iC) {
    BlasCopy(C.X,iC.X);
  }

}

#endif

