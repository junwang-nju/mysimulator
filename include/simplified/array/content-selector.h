
#ifndef _Array_Content_Selector_H_
#define _Array_Content_Selector_H_

#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename T>
  class ArrayContentSelector {

    public:
      static_assert(!__intrinsic_flag<T>::FG,
                    "For intrinsic types, please use Intrinsic<T>!\n");
      typedef T value_type;

  };

}

#include "basic/intrinsic.h"

namespace mysimulator {

  template <typename T>
  class ArrayContentSelector<Intrinsic<T>> {

    public:
      typedef T value_type;
  };

}

#endif

