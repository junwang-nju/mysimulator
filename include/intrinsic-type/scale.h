
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

#include "io/error.h"

namespace mysimulator {

  template <typename T>
  void scale(bool&, const T&) { Error("Scale for bool Not Existed!"); }

  template <typename T>
  void scale(T&, const bool&) { Error("Scale with bool Not Existed!"); }

}

#endif

