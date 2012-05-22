
#ifndef _Basic_Sum_Of_Absolute_H_
#define _Basic_Sum_Of_Absolute_H_

#include "basic/abs-value.h"
#include "type/data.h"
#include "type/is-sumable.h"

namespace mysimulator {

  template <typename T>
  typename DataType<T>::Type _AbsSum(const T& v) {
    typedef typename IsSumable<T>::Type SumCheck;
    return AbsVal(v);
  }

}

#endif

