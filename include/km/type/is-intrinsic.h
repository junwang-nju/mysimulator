
#ifndef _Type_IsIntrinsic_H_
#define _Type_IsIntrinsic_H_

#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T>
  class IsIntrinsicFlag { public: static const bool Flag; };

  template <typename T>
  const bool IsIntrinsicFlag<T>::Flag=IsNumericFlag<T>::Flag;

  template <> const bool IsIntrinsicFlag<bool>::Flag=true;

  template <typename T>
  class IsIntrinsicFlag<T*> { public: static const bool Flag; };

  template <typename T>
  const bool IsIntrinsicFlag<T*>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsIntrinsic {
    public:
      typedef typename Check<IsIntrinsicFlag<T>::Flag>::Type  Type;
  };

}

#endif

