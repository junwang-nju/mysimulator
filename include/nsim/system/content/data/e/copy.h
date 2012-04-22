
#ifndef _System_Content_Data_E_Copy_H_
#define _System_Content_Data_E_Copy_H_

#include "system/content/data/e/interface.h"

namespace mysimulator {

  template <typename T>
  void Copy(SystemContentDataE<T>& D,const SystemContentDataE<T>& iD) {
    D.Energy[0]=iD.Energy[0];
  }

}

#endif

