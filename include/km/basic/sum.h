
/**
 * @file basic/sum.h
 * @brief calculate summation of data with basic type
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Sum_H_
#define _Basic_Sum_H_

#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T>
  T _Sum(const T& v) {
    typedef typename IsNumeric<T>::Type   SumCheck;
    return v;
  }

}

#endif

