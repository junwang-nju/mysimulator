
#ifndef _Basic_Shift_H_
#define _Basic_Shift_H_

#include "type/is-shiftable.h"

namespace mysimulator {

  template <typename T, typename T1>
  void _Shift(T& a, const T1& b) {
    typedef typename IsShiftable<T,T1>::Type  ShiftCheck;
    a+=static_cast<T>(b);
  }

}

#endif

