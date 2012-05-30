
#ifndef _Type_IsCopyAble_H_
#define _Type_IsCopyAble_H_

#include "type/is-included.h"
#include "type/is-numeric.h"
#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsCopyable {
    public:
      static const bool Flag=IsIncluded<T1,T2>::Flag&&
                             IsNumeric<T1>::Flag&&IsNumeric<T2>::Flag;
      typedef typename Check<IsIncluded<T1,T2>::Flag>::Type  Type;
  };

  template <typename T1, typename T2>
  const bool IsCopyable<T1,T2>::Flag;
                                     

}

#endif

