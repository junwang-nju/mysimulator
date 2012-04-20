
#ifndef _System_Content_Data_E_Imprint_H_
#define _System_Content_Data_E_Imprint_H_

#include "system/content/data/e/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentDataE<T>& C, const SystemContentDataE<T>& iC) {
    release(C);
    C.Energy=allocate<T>(1);
    C.isRefer=false;
  }

}

#endif

