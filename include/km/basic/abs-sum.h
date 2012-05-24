
#ifndef _Basic_Sum_Of_Absolute_H_
#define _Basic_Sum_Of_Absolute_H_

#include "basic/abs-value.h"
#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T>
  T _AbsSum(const T& v) {
    typedef typename IsNumeric<T>::Type SumCheck;
    return AbsVal(v);
  }

}

#endif

