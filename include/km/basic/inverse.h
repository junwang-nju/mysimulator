
#ifndef _Basic_Inverse_H_
#define _Basic_Inverse_H_

#include "type/is-float-point.h"

namespace mysimulator {

  template <typename T>
  void _Inverse(T& d) {
    typedef typename IsFloatPoint<T>::Type  FloatPointCheck;
    d=1./d;
  }

}

#endif

