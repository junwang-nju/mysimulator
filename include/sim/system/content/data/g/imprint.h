
#ifndef _System_Content_Data_G_Imprint_H_
#define _System_Content_Data_G_Imprint_H_

#include "system/content/data/g/interface.h"
#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentDataG<T>& C, const SystemContentDataG<T>& iC) {
    release(C);
    imprint(C.Gradient,iC.Gradient);
  }

}

#endif

