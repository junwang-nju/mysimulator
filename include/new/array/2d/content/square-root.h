
#ifndef _Array_2D_Content_SquareRoot_H_
#define _Array_2D_Content_SquareRoot_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/square-root.h"

namespace mysimulator {

  template <typename T>
  void sqroot(Array2DContent<T>& A) { sqroot(A.base); }

}

#endif

