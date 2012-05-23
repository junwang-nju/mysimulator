
#ifndef _Type_IsFloatPoint_H_
#define _Type_IsFloatPoint_H_

namespace mysimulator {

  template <typename T>
  class IsFloatPointFlag { public: static const bool Flag; };

  template <typename T>
  const bool IsFloatPointFlag<T>::Flag=false;

  template <> const bool IsFloatPointFlag<long double>::Flag=true;
  template <> const bool IsFloatPointFlag<double>::Flag=true;
  template <> const bool IsFloatPointFlag<float>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsFloatPoint {
    public:
      typedef typename Check<IsFloatPointFlag<T>::Flag>::Type   Type;
  };

}

#endif

