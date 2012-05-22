
#ifndef _Type_Is_SumAble_H_
#define _Type_Is_SumAble_H_

#include "type/is-numeric.h"
#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsSumableFlag { public: static const bool Flag; };

  template <typename T>
  const bool IsSumableFlag<T>::Flag=IsNumericFlag<T>::Flag;

  template <typename T>
  class IsSumable {
    public:
      typedef typename Check<IsSumableFlag<T>::Flag>::Type  Type;
  };

}

#endif

