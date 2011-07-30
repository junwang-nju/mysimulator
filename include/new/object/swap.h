
#ifndef _Object_Swap_H_
#define _Object_Swap_H_

#include "object/interface.h"
#include "pointer/swap.h"

namespace mysimulator {

  template <typename T>
  void Swap(Object<T>& O1, Object<T>& O2) {
    Swap(static_cast<typename Object<T>::ParentType&>(O1),
         static_cast<typename Object<T>::ParentType&>(O2));
  }

}

#endif

