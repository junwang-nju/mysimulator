
#ifndef _Basic_Type_IntrinsicCheck_H_
#define _Basic_Type_IntrinsicCheck_H_

#include "basic/type/numeric-check.h"

namespace mysimulator {

  template <typename T>
  class __intrinsic { public: static const bool FLAG; };

  template <typename T>
  const bool __intrinsic<T>::FLAG = __numeric<T>::FLAG;

  template <>
  const bool __intrinsic<bool>::FLAG = true;

}

#endif

