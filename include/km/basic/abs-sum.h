
#ifndef _Basic_Sum_Of_Absolute_H_
#define _Basic_Sum_Of_Absolute_H_

#include "basic/abs-value.h"
#include "basic/data-type.h"
#include "type-check/is-sumable.h"
#include "type-check/is-numeric.h"

namespace mysimulator {

  template <typename T>
  typename DataType<T>::Type _AbsSum(const T& v) {
    typedef typename IsSumable<T>::Type SumCheck;
    typedef typename IsNumeric<T>::Type NumericCheck;
    return AbsVal(v);
  }

}

#endif

