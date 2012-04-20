
#ifndef _System_Content_Data_EG_Copy_H_
#define _System_Content_Data_EG_Copy_H_

#include "system/content/data/eg/interface.h"
#include "array/2d/copy.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentDataEG<T>& D,const SystemContentDataEG<T>& iD) {
    Copy(*(D.Energy),*(iD.Energy));
    Copy(D.Gradient,iD.Gradient);
  }

}

#endif

