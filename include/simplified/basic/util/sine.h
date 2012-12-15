
#ifndef _Basic_Utility_Sine_H_
#define _Basic_Utility_Sine_H_

#include <cmath>

namespace mysimulator {

  float   __sin(float f) { return sinf(f); }
  double  __sin(double d) { return sin(d); }
  long double __sin(long double d) { return sinl(d); }

}

#endif

