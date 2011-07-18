
#ifndef _Intrinsic_Type_Valid_H_
#define _Intrinsic_Type_Valid_H_

#include "intrinsic-type/reflection/single.h"

namespace mysimulator {

  template <typename T>
  bool IsValid(const T&) { typedef typename _Single<T>::Type Type;return true; }

}

#include <cstdlib>

namespace mysimulator {

  template <typename T>
  bool IsValid(const T* const& ptr) { return ptr!=NULL; }

}

#endif

