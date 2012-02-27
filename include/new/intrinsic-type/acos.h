
#ifndef _Intrinsic_Type_ArcCosine_H_
#define _Intrinsic_Type_ArcCosine_H_

#include <cmath>

#define _ACOS(type) type arcCos(const type& d)

namespace mysimulator {

  _ACOS(double) { return acos(d); }
  _ACOS(float) { return acos(d); }
  _ACOS(long double) { return acosl(d); }

}

#endif

