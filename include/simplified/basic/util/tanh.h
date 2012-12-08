
#ifndef _Basic_Utility_TanH_H_
#define _Basic_Utility_TanH_H_

#include <cmath>

namespace mysimulator {

  double __tanh(double d) { return tanh(d); }
  float __tanh(float f) { return tanhf(f); }
  long double __tanh(long double d) { return tanhl(d); }

}

#endif

