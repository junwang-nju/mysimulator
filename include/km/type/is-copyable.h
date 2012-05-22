
#ifndef _Type_IsCopyAble_H_
#define _Type_IsCopyAble_H_

namespace mysimulator {

  template <typename T1, typename T2>
  class IsCopyableFlag {
    public: static const bool Flag;
  };

  template <typename T>
  const bool IsCopyableFlag<T*,T*>::Flag=true;

  template <typename T>
  const bool IsCopyableFlag<void*,T*>::Flag=true;

  template <typename T>
  const bool IsCopyableFlag<T*,void*>::Flag=true;

}

#include "type/is-included.h"
#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T1, typename T2>
  const bool IsCopyableFlag<T1,T2>::Flag=
    IsIncluded<T1,T2>::Flag&&IsNumeric<T1>::Flag&&IsNumeric<T2>::Flag;

}

#include "type/is-integer.h"

namespace mysimulator {

  template <typename T>
  const bool IsCopyableFlag<bool,T>::Flag=IsInteger<T>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsCopyable {
    public:
      typedef typename Check<IsCopyableFlag<T1,T2>::Flag>::Type  Type;
  };

}

#endif

