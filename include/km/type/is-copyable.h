
#ifndef _Type_IsCopyAble_H_
#define _Type_IsCopyAble_H_

#include "type/is-included.h"
#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsCopyable {
    public:
      typedef typename Check<IsIncluded<T1,T2>::Flag>::Type  Type;
  };

}

#endif

