
#ifndef _Array_2D_Content_Norm_H_
#define _Array_2D_Content_Norm_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/norm.h"

namespace mysimulator {

  template <typename T>
  T normSQ(const Array2DContent<T>& A) { return normSQ(A.base); }

  template <typename T>
  T norm(const Array2DContent<T>& A) { return norm(A.base); }

}

#endif

