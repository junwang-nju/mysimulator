
#ifndef _Intrinsic_Type_Sine_H_
#define _Intrinsic_Type_Sine_H_

#include <cmath>

#define _SIN(type,func) type Sine(const type& d) { return func(d); }

namespace mysimulator {

  _SIN(double,sin)
  _SIN(float,sinf)
  _SIN(long double,sinl)

}

#undef _SIN

#endif

