
#ifndef _Type_IsCopyAble_H_
#define _Type_IsCopyAble_H_

#include "type/is-included.h"
#include "type/is-numeric.h"
#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsCopyableFlag {
    public: static const bool Flag;
  };

  template <typename T1, typename T2>
  const bool IsCopyableFlag<T1,T2>::Flag=
    IsIncluded<T1,T2>::Flag&&IsNumeric<T1>::Flag&&IsNumeric<T2>::Flag;

  template <typename T1, typename T2>
  class IsCopyable {
    public:
      typedef typename Check<IsCopyableFlag<T1,T2>::Flag>::Type  Type;
  };

}

#endif

