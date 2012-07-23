
#ifndef _Basic_Tanh_H_
#define _Basic_Tanh_H_

#include <cmath>

#define _TANH_(RT,Func) T _Tanh(const T& d) { return Func(d); }

namespace mysimulator {

  _TANH_(double,tanh)
  _TANH_(float,tanhf)
  _TANH_(long double,tanhl)

}

#undef _TANH_

#endif

