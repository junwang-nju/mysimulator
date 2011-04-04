
#ifndef _Intrinsic_Type_Compare_H_
#define _Intrinsic_Type_Compare_H_

#include "intrinsic-type/operation-type.h"

namespace mysimulator {

  template <typename T1, typename T2>
  int compare(const T1& d1, const T2& d2) {
    typedef typename _Operation<T1,T2>::Type Type;
    return static_cast<Type>(d1)==static_cast<Type>(d2)?0:
          (static_cast<Type>(d1)<static_cast<Type>(d2)?-1:1);
  }

}

#endif

