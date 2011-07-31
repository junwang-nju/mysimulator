
#ifndef _Array_2D_Swap_H_
#define _Array_2D_Swap_H_

#include "array/2d/interface.h"
#include "array/2d/content/swap.h"
#include "array/format/swap.h"

namespace mysimulator {

  template <typename T>
  void Swap(Array2D<T>& A1, Array2D<T>& A2) {
    typedef typename Array2D<T>::ParentType   Type;
    Swap(static_cast<Type&>(A1),static_cast<Type&>(A2));
    Swap(A1.subdata,A2.subdata);
  }

}

#endif

