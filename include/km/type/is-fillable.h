
#ifndef _Type_IsFillAble_H_
#define _Type_IsFillAble_H_

namespace mysimulator {

  template <typename T1, typename T2>
  class IsFillableFlag {
    public: static const bool Flag;
  };

  template <> const bool IsFillableFlag<bool,bool>::Flag=true;

}

#include "type/is-included.h"
#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T1, typename T2>
  const bool IsFillableFlag<T1,T2>::Flag=
    IsIncluded<T1,T2>::Flag&&IsNumeric<T1>::Flag&&IsNumeric<T2>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsFillable {
    public: typedef typename Check<IsFillableFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

