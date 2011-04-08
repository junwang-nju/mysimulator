
#ifndef _Vector_Compare_H_
#define _Vector_Compare_H_

#include "vector/interface.h"

namespace mysimulator {

  template <typename Ta, typename Tb>
  bool IsSameStructure(const Vector<Ta>& va, const Vector<Tb>& vb) {
    return va.size==vb.size;
  }

}

#endif

