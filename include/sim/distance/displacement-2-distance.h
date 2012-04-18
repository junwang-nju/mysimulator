
#ifndef _Displacement_To_Distance_H_
#define _Displacement_To_Distance_H_

#include "array/1d/norm.h"

namespace mysimulator {

  // assuming n is small
  template <typename T>
  T Displacement2DistanceSQ(const T* p, unsigned int n) { return NormSQ(p,n); }

  // assuming n is small
  template <typename T>
  T Displacement2Distance(const T* p, unsigned int n) { return Norm(p,n); }

}

#endif

