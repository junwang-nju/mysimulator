
#ifndef _Intrinsic_Type_Fill_H_
#define _Intrinsic_Type_Fill_H_

#include "intrinsic-type/assign-type.h"

namespace mysimulator {

  template <typename T, typename T1>
  void fill(T& a, const T1& b) {
    typedef typename _Assign<T,T1>::Type  Type;
    a=static_cast<Type>(b);
  }

  void fill(bool& b, const bool& rb) { b=rb; }
  template <typename T>
  void fill(bool& b, const T& i) {
    typedef typename _Assign<bool,T>::Type  Type;
    b=(i==0?false:true);
  }

}

#endif

