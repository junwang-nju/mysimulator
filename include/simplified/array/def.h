
#ifndef _Array_Def_H_
#define _Array_Def_H_

#include "array/monomer/value/flag.h"
#include "array/kernel/name.h"

namespace mysimulator {

  template <typename T,ArrayKernelName KN=ArrayKernelName::Simple,
                       bool _vFlag=__array_value<T>::FLAG>
  class Array {

    public:

      typedef Array<T,KN,_vFlag>  Type;

      Array() = delete;
      Array(const Type&) = delete;
      ~Array() {}

      Type& operator=(const Type&) = delete;

  };

}

#endif

