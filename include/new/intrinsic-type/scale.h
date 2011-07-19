
#ifndef _Intrinsic_Type_Scale_H_
#define _Intrinsic_Type_Scale_H_

#include "intrinsic-type/reflection/dual.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void scale(T1& a, const T2& b) {
    typedef typename _Dual<T1,T2>::AssignType Type;
    a*=static_cast<const Type&>(b);
  }

}

#endif

