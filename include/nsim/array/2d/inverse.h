
#ifndef _Array_2D_Inverse_H_
#define _Array_2D_Inverse_H_

#include "array/2d/interface.h"
#include "array/1d/inverse.h"

namespace mysimulator {

  template <typename T>
  void Inverse(Array2D<T>& V) { Inverse(V._ldata,V._ldata.Size()); }

}

#endif

