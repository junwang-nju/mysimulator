
#ifndef _Intrinsic_Type_SquareRoot_H_
#define _Intrinsic_Type_SquareRoot_H_

#include <cmath>

#define _SQROOT(type) type sqroot(const type& d)

namespace mysimulator {

  _SQROOT(long double) { return sqrtl(d); }
  _SQROOT(double) { return sqrt(d); }
  _SQROOT(float) { return sqrtf(d); }

}

#undef _SQROOT

#endif

