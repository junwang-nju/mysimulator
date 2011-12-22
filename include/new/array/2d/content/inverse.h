
#ifndef _Array_2D_Content_Inverse_H_
#define _Array_2D_Content_Inverse_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/inverse.h"

namespace mysimulator {

  template <typename T>
  void inverse(Array2DContent<T>& A) { inverse(A.base); }

}

#endif

