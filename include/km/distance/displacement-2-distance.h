
#ifndef _Distance_Displacement2Distance_H_
#define _Distance_Displacement2Distance_H_

#include "array-numeric/interface.h"

namespace mysimulator {

  template <typename T>
  T Displacement2DistanceSQ(const ArrayNumeric<T>& A) { return A.NormSQ(); }

  template <typename T>
  T Displacement2Distance(const ArrayNumeric<T>& A) { return A.Norm(); }

}

#endif

