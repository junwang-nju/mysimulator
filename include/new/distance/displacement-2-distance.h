
#ifndef _Displacement_To_Distance_H_
#define _Displacement_To_Distance_H_

#include "array/1d/content/norm.h"

namespace mysimulator {

  template <typename T>
  T Displacement2DistanceSQ(const Array1DContent<T>& A) { return normSQ(A); }

  template <typename T>
  T Displacement2Distance(const Array1DContent<T>& A) { return norm(A); }

}

#endif

