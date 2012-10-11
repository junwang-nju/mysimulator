
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "array/container.h"

namespace mysimulator {

  template <typename T,ArrayFormat AF>
  class Array {
    public:
      static_assert(!__intrinsic_flag<T>::FG,
                    "For Intrinsic Type, please use Intrinsic<T>!\n");
      typedef Array<T,AF>   Type;
      Array() = delete;
      Array(Type const&) = delete;
      ~Array();
      Type& operator=(const Type&) = delete;
  };

}

#include "array/regular.h"
#include "array/short-data.h"
#include "array/large-data.h"

#include "array/expression-sum.h"
#include "array/expression-substract.h"
#include "array/expression-multiple.h"
#include "array/expression-divide.h"

#endif

