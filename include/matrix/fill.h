
#ifndef _Matrix_Fill_H_

#include "matrix/interface.h"
#include "list/fill.h"

namespace mysimulator {

  template <typename T, typename sT>
  void fill(Matrix<T>& M, const sT& value) {
    fill(static_cast<List<T>&>(M),value);
  }

}

#endif

