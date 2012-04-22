
#ifndef _System_Content_Data_G_Imprint_H_
#define _System_Content_Data_G_Imprint_H_

#include "system/content/data/g/interface.h"

namespace mysimulator {

  template <typename T>
  void Imprint(SystemContentDataG<T>& D,const SystemContentDataG<T>& iD) {
    D.Allocate(iD.Gradient);
  }

}

#endif

