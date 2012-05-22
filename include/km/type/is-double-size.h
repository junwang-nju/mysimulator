
#ifndef _Type_IsDoubleSize_H_
#define _Type_IsDoubleSize_H_

namespace mysimulator {

  template <typename T>
  class IsDoubleSizeFlag { public: static const bool Flag; };

  template <typename T> const bool IsDoubleSizeFlag<T>::Flag=
    (sizeof(double)==sizeof(T));

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsDoubleSize {
    public:
      typedef typename Check<IsDoubleSizeFlag<T>::Flag>::Type   Type;
  };

}

#endif

