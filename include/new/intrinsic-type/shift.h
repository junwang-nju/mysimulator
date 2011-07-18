
#ifndef _Intrinsic_Type_Shift_H_
#define _Intrinsic_Type_Shift_H_

#include "intrinsic-type/reflection/dual.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3>
  void shift(T1& a, const T2& b, const T3& c) {
    typedef typename _Dual<T2,T3>::CombineType  SumType;
    typedef typename _Dual<T1,SumType>::AssignType Type;
    a+=static_cast<Type>(b)*static_cast<Type>(c);
  }

}

#endif

