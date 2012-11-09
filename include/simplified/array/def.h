
#ifndef _Array_Def_H_
#define _Array_Def_H_

#include "array/value-flag.h"

namespace mysimulator {

  template <typename T, bool _vflag=__array_value<T>::FLAG>
  class Array {

    public:

      typedef Array<T,_vflag>   Type;
      Array() = delete;
      Array(const Type&) = delete;
      Type& operator=(const Type&) = delete;
      ~Array() {}

  };

}

#endif

