
#ifndef _System_Content_Data_E_Allocate_H_
#define _System_Content_Data_E_Allocate_H_

#include "system/content/data/e/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(SystemContentDataE<T>& D) {
    release(D);
    D.Energy=allocate<T>(1);
    D.isRefer=false;
  }

}

#endif

