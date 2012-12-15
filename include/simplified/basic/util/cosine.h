
#ifndef _Basic_Utility_Cosine_H_
#define _Basic_Utility_Cosine_H_

#include <cmath>

namespace mysimulator {

  float   __cos(float d) { return cosf(d); }
  double  __cos(double d) { return cos(d); }
  long double __cos(long double d) { return cosl(d); }

}

#endif

