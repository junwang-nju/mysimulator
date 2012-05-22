
#ifndef _Type_Is_SumAble_H_
#define _Type_Is_SumAble_H_

#include "type/is-numeric.h"
#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsSumable {
    public:
      typedef typename Check<IsNumeric<T>::Flag>::Type  Type;
  };

}

#endif

