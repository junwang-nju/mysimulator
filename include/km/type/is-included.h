
#ifndef _Type_IsIncluded_H_
#define _Type_IsIncluded_H_

namespace mysimulator {

  template <typename T1, typename T2>
  class IsIncludedFlag {
    public:
      static const bool Flag;
  };

}

#include "type/is-float-point.h"
#include "type/is-integer.h"
#include "type/is-unsigned.h"

namespace mysimulator {

  template <typename T1, typename T2>
  const bool IsIncludedFlag<T1,T2>::Flag=
    ( IsFloatPointFlag<T1>::Flag && IsFloatPointFlag<T2>::Flag 
                                 && (sizeof(T1)>=sizeof(T2)) ) ||
    ( IsFloatPointFlag<T1>::Flag && IsIntegerFlag<T2>::Flag ) ||
    ( IsIntegerFlag<T1>::Flag && (!IsUnsignedFlag<T1>::Flag)
                              && IsIntegerFlag<T2>::Flag
                              && (sizeof(T1)>sizeof(T2)) ) ||
    ( IsIntegerFlag<T1>::Flag && IsIntegerFlag<T2>::Flag && (sizeof(T1)==sizeof(T2))
                              && (!IsUnsignedFlag<T1>::Flag)
                              && (!IsUnsignedFlag<T2>::Flag) ) ||
    ( IsUnsignedFlag<T1>::Flag && IsUnsignedFlag<T2>::Flag
                               && (sizeof(T1)>=sizeof(T2)) );

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1,typename T2>
  class IsIncluded {
    public:
      typedef typename Check<IsIncludedFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

