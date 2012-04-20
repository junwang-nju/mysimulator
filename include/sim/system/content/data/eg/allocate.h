
#ifndef _System_Content_Data_EG_Allocate_H_
#define _System_Content_Data_EG_Allocate_H_

#include "system/content/data/eg/interface.h"
#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T>
  void allocate(SystemContentDataEG<T>& D, const T** X) {
    release(D);
    D.Energy=allocate<T>(1);
    D.isRefer=false;
    imprint(D.Gradient,X);
  }

}

#endif

