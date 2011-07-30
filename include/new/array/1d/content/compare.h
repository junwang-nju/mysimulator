
#ifndef _Array_1D_Content_Compare_H_
#define _Array_1D_Content_Compare_H_

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T1, typename T2>
  bool IsSameSize(const Array1DContent<T1>& va, const Array1DContent<T2>& vb) {
    return va.size==vb.size;
  }

}

#endif

