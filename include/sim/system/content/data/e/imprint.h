
#ifndef _System_Content_Data_E_Imprint_H_
#define _System_Content_Data_E_Imprint_H_

#include "system/content/data/e/allocate.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentDataE<T>& C, const SystemContentDataE<T>&) {
    allocate(C);
  }

}

#endif

