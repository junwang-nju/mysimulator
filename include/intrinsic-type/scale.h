
#ifndef _Intrinsic_Type_Scale_H_
#define _Intrinsic_Type_Scale_H_

#include "intrinsic-type/assign-type.h"

namespace mysimulator {

  template <typename T, typename T1>
  void scale(T& a, const T1& b) {
    typedef typename _Assign<T,T1>::Type   Type;
    a*=static_cast<Type>(b);
  }

}

#endif

