
#ifndef _Array_1D_Swap_H_
#define _Array_1D_Swap_H_

#include "array/1d/interface.h"
#include "pointer/swap.h"

namespace mysimulator {

  template <typename T>
  void swap(Array1D<T>& v1, Array1D<T>& v2) {
    typedef typename Array1D<T>::ParentType PType;
    swap(static_cast<PType&>(v1),static_cast<PType&>(v2));
    exchange(v1.first,v2.first);
    exchange(v1.last,v2.last);
    exchange(v1.head,v2.head);
    exchange(v1.start,v2.start);
  }

}

#endif

