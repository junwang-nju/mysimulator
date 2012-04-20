
#ifndef _System_Content_Data_G_Imprint_H_
#define _System_Content_Data_G_Imprint_H_

#include "system/content/data/g/allocate.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentDataG<T>& C, const SystemContentDataG<T>& iC) {
    allocate(C,iC.Gradient);
  }

}

#endif

