
#ifndef _Basic_Sum_H_
#define _Basic_Sum_H_

#include "type/data.h"
#include "type/is-sumable.h"

namespace mysimulator {

  template <typename T>
  typename DataType<T>::Type _Sum(const T& v) {
    typedef typename IsSumable<T>::Type   SumCheck;
    return v;
  }

}

#endif

