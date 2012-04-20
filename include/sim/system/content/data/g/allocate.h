
#ifndef _System_Content_Data_G_Allocate_H_
#define _System_Content_Data_G_Allocate_H_

#include "system/content/data/g/interface.h"
#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T>
  void allocate(SystemContentDataG<T>& D, const T** X) {
    release(D);
    imprint(D.Gradient,X);
  }

}

#endif

