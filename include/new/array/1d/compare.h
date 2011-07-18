
#ifndef _Array_1D_Compare_H_
#define _Array_1D_Compare_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename Ta, typename Tb>
  bool IsSameSize(const Array1D<Ta>& va, const Array1D<Tb>& vb) {
    return va.size==vb.size;
  }

}

#endif

