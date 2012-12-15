
#ifndef _Basic_Utility_ArcCos_H_
#define _Basic_Utility_ArcCos_H_

#include <cmath>

namespace mysimulator {

  double  __acos(double d) { return acos(d); }
  float   __acos(float d) { return acosf(d); }
  long double __acos(long double d) { return acosl(d); }

}

#endif

