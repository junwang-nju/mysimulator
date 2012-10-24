
#ifndef _Array_Content_Selector_H_
#define _Array_Content_Selector_H_

#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename T>
  class ArrayContentSelector {
    public:
      static_assert(!__intrinsic_flag<T>::FG,
                    "For intrinsic types, please use Intrinsic<T>!\n");
      typedef T monomer_type;
      static const bool _has_value;
  };

  template <typename T>
  const bool ArrayContentSelector<T>::_has_value=false;

}

#include "basic/intrinsic.h"

namespace mysimulator {

  template <typename T>
  class ArrayContentSelector<Intrinsic<T>> {
    public:
      typedef T monomer_type;
      typedef T value_type;
      static const bool _has_value;
  };

  template <typename T>
  const bool ArrayContentSelector<Intrinsic<T>>::_has_value=true;

  template <typename T,bool _vflag> class Array;

  template <typename T>
  class ArrayContentSelector<Array<T,true>> {
    public:
      typedef Array<T,true>             monomer_type;
      typedef typename T::value_type    value_type;
      static const bool _has_value;
  };

  template <typename T>
  const bool ArrayContentSelector<Array<T,true>>::_has_value=true;

}

#endif

