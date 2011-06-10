
#ifndef _Matrix_Swap_H_
#define _Matrix_Swap_H_

#include "matrix/interface.h"
#include "list/swap.h"
#include "referable-object/swap.h"
#include "generic/exchange.h"

namespace mysimulator {

  template <typename T>
  void swap(Matrix<T>& Ma, Matrix<T>& Mb) {
    swap(Ma.property,Mb.property);
    swap(Ma.other,Mb.other);
    exchange(Ma.GetFunc,Mb.GetFunc);
    swap(static_cast<List<T>&>(Ma),static_cast<List<T>&>(Mb));
  }

}

#endif

