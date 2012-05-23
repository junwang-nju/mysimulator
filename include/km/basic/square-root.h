
#ifndef _Basic_SquareRoot_H_
#define _Basic_SquareRoot_H_

#include <cmath>

#ifndef _SQROOT_
#define _SQROOT_(T,Func)  T __SqRoot(const T& d) { return Func(d); }
#else
#error "Duplicate _SQROOT_"
#endif

namespace mysimulator {

  _SQROOT_(long double, sqrtl)
  _SQROOT_(double,      sqrt)
  _SQROOT_(float,       sqrtf)

}

#ifdef _SQROOT_
#undef _SQROOT_
#endif

#include "type/is-float-point.h"

namespace mysimulator {

  template <typename T>
  void _SqRoot(T& d) {
    typedef typename IsFloatPoint<T>::Type  FloatPointCheck;
    d=__SqRoot(d);
  }

}

#endif

