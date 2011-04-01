
#ifndef _Intrinsic_Type_Fill_H_
#define _Intrinsic_Type_Fill_H_

#include "intrinsic/copy.h"

namespace mysimulator {

  template <typename T, typename cT>
  void fill(T& a, const cT& b) { copy(a,b); }

}

#endif

