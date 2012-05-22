
#ifndef _Basic_Sum_H_
#define _Basic_Sum_H_

#include "type-check/is-sumable.h"

namespace mysimulator {

  template <typename T>
  const T& _Sum(const T& v) {
    typedef typename IsSumable<T>::Type   SumCheck;
    return v;
  }

}

#endif

