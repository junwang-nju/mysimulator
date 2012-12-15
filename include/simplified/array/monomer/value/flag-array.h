
#ifndef _Array_Monomer_Value_Flag_Array_H_
#define _Array_Monomer_Value_Flag_Array_H_

#include "array/monomer/value/flag-def.h"
#include "array/kernel/name.h"

namespace mysimulator {

  template <typename,ArrayKernelName KN,bool> class Array;

  template <typename T,ArrayKernelName KN>
  class __array_value<Array<T,KN,true>> { public: static const bool FLAG; };

  template <typename T,ArrayKernelName KN>
  const bool __array_value<Array<T,KN,true>>::FLAG = true;

}

#endif

