
#ifndef _System_Content_Data_EG_Imprint_H_
#define _System_Content_Data_EG_Imprint_H_

#include "system/content/data/eg/allocate.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentDataEG<T>& C, const SystemContentDataEG<T>& iC) {
    allocate(C,iC.Gradient);
  }

}

#endif

