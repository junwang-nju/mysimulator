
/**
 * @file basic/abs-sum.h
 * @brief calculate summation of absolute value for basic data
 *
 * To be compatible with ArrayNumeric object, the similar operation to
 * calculate the summation of the absolute value of object should be
 * introduced. this file implements this operation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Sum_Of_Absolute_H_
#define _Basic_Sum_Of_Absolute_H_

#include "basic/abs-value.h"
#include "type/is-numeric.h"

namespace mysimulator {

  /** @fn T _AbsSum(const T&)
   * @brief summation of absolute value of object
   *
   * This generalizd template format is used only for intrinsic data type
   * to avoid side effect. The check is implemented with IsNumeric. The
   * result is the absolute value of input number.
   *
   * @tparam T the type of input data
   *
   * @param v the input T-type object
   * @return the absolute value of input number
   */
  template <typename T>
  T _AbsSum(const T& v) {
    typedef typename IsNumeric<T>::Type SumCheck;
    return AbsVal(v);
  }

}

#endif

