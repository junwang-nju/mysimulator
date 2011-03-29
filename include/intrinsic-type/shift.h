
#ifndef _Intrinsic_Type_Shift_H_
#define _Intrinsic_Type_Shift_H_

#include "intrinsic-type/assign-type.h"
#include "intrinsic-type/operation-type.h"

namespace mysimulator {

  template <typename T, typename T1, typename T2>
  void shift(T& a, const T1& b, const T2& c) {
    typedef typename _Assign<T,typename _Operation<T1,T2>::Type>::Type
            Type;
    a+=static_cast<Type>(b)*static_cast<Type>(c);
  }

}

#endif

