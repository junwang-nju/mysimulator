
#ifndef _Basic_Util_SquareRoot_H_
#define _Basic_Util_SquareRoot_H_

#include <cmath>

namespace mysimulator {

  double __square_root(double const& D) { return sqrt(D); }
  float __square_root(float const& D) { return sqrt(D); }
  long double __square_root(long double const& D) { return sqrtl(D); }

}

#endif

