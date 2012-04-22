
#ifndef _Array_2D_Norm_H_
#define _Array_2D_Norm_H_

#include "array/2d/interface.h"
#include "array/1d/norm.h"

namespace mysimulator {

  template <typename T>
  T NormSQ(const Array2D<T>& V) { return NormSQ(V._ldata,V._ldata.Size()); }

  template <typename T>
  T BlasNormSQ(const Array2D<T>& V) {
    return BlasNormSQ(V._ldata,V._ldata.Size());
  }

  template <typename T>
  T Norm(const Array2D<T>& V) { return Norm(V._ldata,V._ldata.Size()); }

  template <typename T>
  T BlasNorm(const Array2D<T>& V) { return BlasNorm(V._ldata,V._ldata.Size()); }

}

#endif

