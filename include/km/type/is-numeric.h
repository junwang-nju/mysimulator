
#ifndef _Type_IsNumeric_H_
#define _Type_IsNumeric_H_

#include "type/is-float-point.h"
#include "type/is-integer.h"

namespace mysimulator {

  template <typename T>
  class IsNumericFlag { public: static const bool Flag; };

  template <typename T> const bool IsNumericFlag<T>::Flag=
    IsFloatPointFlag<T>::Flag||IsIntegerFlag<T>::Flag;

  union Unique64Bit;
  template <> const bool IsNumericFlag<Unique64Bit>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsNumeric {
    public:
      typedef typename Check<IsNumericFlag<T>::Flag>::Type   Type;
  };

}

#endif

