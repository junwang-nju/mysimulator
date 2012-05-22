
#ifndef _Basic_Sum_H_
#define _Basic_Sum_H_

#include "type-check/is-sumable.h"
#include "type-check/is-numeric.h"

namespace mysimulator {

  template <typename T>
  const T& _Sum(const T& v) {
    typedef typename IsSumable<T>::Type   SumCheck;
    typedef typename IsNumeric<T>::Type   NumericCheck;
    return v;
  }

}

#endif

