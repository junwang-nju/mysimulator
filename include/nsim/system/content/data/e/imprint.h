
#ifndef _System_Content_Data_E_Imprint_H_
#define _System_Content_Data_E_Imprint_H_

#include "system/content/data/e/interface.h"

namespace mysimulator {

  template <typename T>
  void Imprint(SystemContentDataE<T>& C,const SystemContentDataE<T>&) {
    C.Allocate();
  }

}

#endif

