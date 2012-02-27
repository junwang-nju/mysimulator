
#ifndef _Intrinsic_Type_ArcCosine_H_
#define _Intrinsic_Type_ArcCosine_H_

#include <cmath>

#define _ACOS(type,func) type arcCos(const type& d) { return func(d); }

namespace mysimulator {

  _ACOS(double,acos)
  _ACOS(float,acosf)
  _ACOS(long double,acosl)

}

#undef _ACOS

#endif

