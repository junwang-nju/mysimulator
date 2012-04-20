
#ifndef _System_Content_Data_G_Copy_H_
#define _System_Content_Data_G_Copy_H_

#include "system/content/data/g/interface.h"
#include "array/2d/copy.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentDataG<T>& D, const SystemContentDataG<T>& iD) {
    BLASCopy(D.Gradient,iD.Gradient);
  }

}

#endif

