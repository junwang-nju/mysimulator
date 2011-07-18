
#ifndef _Intrinsic_Type_Duplicate_H_
#define _Intrinsic_Type_Duplicate_H_

#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void duplicate(T1& d, const T2& d2) {
    typedef typename _Dual<T1,T2>::AssignType Type;
    copy(d,d2);
  }

}

#endif

