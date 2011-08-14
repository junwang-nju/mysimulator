
#ifndef _Array_2D_Content_Sum_H_
#define _Array_2D_Content_Sum_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/sum.h"

namespace mysimulator {

  template <typename T>
  T sum(const Array2DContent<T>& A) { return sum(A.base); }

}

#endif

