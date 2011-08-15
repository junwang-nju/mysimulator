
#ifndef _Object_Swap_H_
#define _Object_Swap_H_

#include "object/interface.h"
#include "pointer/swap.h"

namespace mysimulator {

  template <typename T>
  void Swap(Object<T>& O1, Object<T>& O2) {
    typedef typename Object<T>::ParentType  Type;
    Swap(static_cast<Type&>(O1),static_cast<Type&>(O2));
  }

}

#endif

