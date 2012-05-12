
#ifndef _Intrinsic_Type_Sine_H_
#define _Intrinsic_Type_Sine_H_

#include <cmath>

#ifndef _SIN
#define _SIN(T,Func) T Sine(const T& d) { return Func(d); }
#else
#error "Duplicate Definition for Macro _SIN"
#endif

namespace mysimulator {

  _SIN(double,sin)
  _SIN(float,sinf)
  _SIN(long double,sinl)

}

#ifdef _SIN
#undef _SIN
#endif

#endif

