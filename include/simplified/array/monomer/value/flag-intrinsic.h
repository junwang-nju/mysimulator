
#ifndef _Array_Monomer_Value_Flag_Intrinsic_H_
#define _Array_Monomer_Value_Flag_Intrinsic_H_

#include "array/monomer/value/flag-def.h"

namespace mysimulator {

  template <typename T> class Intrinsic;

  template <typename T>
  class __array_value<Intrinsic<T>> { public: static const bool FLAG; };

  template <typename T>
  const bool __array_value<Intrinsic<T>>::FLAG = true;

}

#endif

