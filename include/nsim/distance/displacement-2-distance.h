
#ifndef _Distance_Displacement2Distance_H_
#define _Distance_Displacement2Distance_H_

#include "array/1d/norm.h"

namespace mysimulator {

  template <typename T>
  T Displacement2DistanceSQ(const Array1D<T>& V,unsigned int n) {
    return NormSQ(V,n);
  }

  template <typename T>
  T Displacement2Distance(const Array1D<T>& V,unsigned int n) {
    return Norm(V,n);
  }

}

#endif

