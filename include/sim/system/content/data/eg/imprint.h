
#ifndef _System_Content_Data_EG_Imprint_H_
#define _System_Content_Data_EG_Imprint_H_

#include "system/content/data/eg/interface.h"
#include "array/2d/imprint.h"

namespace mysimulator {

  template <typename T>
  void imprint(SystemContentDataEG<T>& C, const SystemContentDataEG<T>& iC) {
    release(C);
    C.Energy=allocate<T>(1);
    C.isRefer=false;
    imprint(C.Gradient,iC.Gradient);
  }

}

#endif

