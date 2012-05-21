
#ifndef _Intrinsic_Type_SquareRoot_H_
#define _Intrinsic_Type_SquareRoot_H_

#include <cmath>

#define _SQROOT(type,func) type Sqroot(const type& d) { return func(d); }

namespace mysimulator {

  _SQROOT(long double,sqrtl)
  _SQROOT(double,sqrt)
  _SQROOT(float,sqrtf)

}

#undef _SQROOT

#endif

