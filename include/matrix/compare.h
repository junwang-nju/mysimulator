
#ifndef _Matrix_Compare_H_
#define _Matrix_Compare_H_

#include "matrix/interface.h"
#include "matrix/property/compare.h"

namespace mysimulator {

  template <typename Ta, typename Tb>
  bool IsPropertySame(const Matrix<Ta>& Ma, const Matrix<Tb>& Mb) {
    return IsPropertySame(Ma.property,Mb.property);
  }

}

#endif

