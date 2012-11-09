
#ifndef _Basic_Type_Intrinsic_H_
#define _Basic_Type_Intrinsic_H_

#include "basic/type/numeric.h"

namespace mysimulator {

  template <typename T>
  class __intrinsic_flag {
    public: static const bool FG;
  };

  template<typename T> const bool __intrinsic_flag<T>::FG=__numeric_flag<T>::FG;
  template<> const bool __intrinsic_flag<bool>::FG=true;

}

#endif

