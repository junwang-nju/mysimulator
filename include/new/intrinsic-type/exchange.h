
#ifndef _Intrinsic_Type_Exchange_H_
#define _Intrinsic_Type_Exchange_H_

#include "intrinsic-type/reflection/single.h"

namespace mysimulator {

  template <typename T>
  void exchange(T& a, T& b) { typename _Single<T>::Type c; c=a; a=b; b=c; }

}

#endif

