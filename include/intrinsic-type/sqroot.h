
#ifndef _Intrinsic_Type_Square_Root_H_
#define _Intrinsic_Type_Square_Root_H_

#include <cmath>

namespace mysimulator {

  long double sqroot(const long double& ld) { return sqrtl(ld); }
  double sqroot(const double& d) { return sqrt(d); }
  float sqroot(const float& f) { return sqrtf(f); }

}

#endif

