
#ifndef _List_Swap_H_
#define _List_Swap_H_

#include "list/interface.h"
#include "vector/swap.h"

namespace mysimulator {

  template <typename T>
  void swap(List<T>& La, List<T>& Lb) {
    swap(La.infra,Lb.infra);
    swap(static_cast<Vector<T>&>(La),static_cast<Vector<T>&>(Lb));
  }

}

#endif

