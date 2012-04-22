
#ifndef _System_Content_Data_EG_Imprint_H_
#define _System_Content_Data_EG_Imprint_H_

#include "system/content/data/eg/interface.h"

namespace mysimulator {

  template <typename T>
  void Imprint(SystemContentDataEG<T>& D,const SystemContentDataEG<T>& iD) {
    D.Allocate(iD.Gradient);
  }

}

#endif

