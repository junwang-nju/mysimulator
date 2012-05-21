
#ifndef _Array_2D_SquareRoot_H_
#define _Array_2D_SquareRoot_H_

#include "array/2d/interface.h"
#include "array/1d/square-root.h"

namespace mysimulator {

  template <typename T>
  void Sqroot(Array2D<T>& V) { Sqroot(V._ldata); }

}

#endif

