
#ifndef _Basic_SquareRoot_H_
#define _Basic_SquareRoot_H_

#include <cmath>

namespace mysimulator {

  double __SquareRoot(double const& D) { return sqrt(D); }
  float __SquareRoot(float const& D) { return sqrtf(D); }
  long double __SquareRoot(long double const& D) { return sqrtl(D); }

}

#endif

