
/**
 * @file basic/inverse.h
 * @brief calculate inverse for data of basic type
 *
 * To be compatible with the \c ArrayNumeric object, the operation inverse
 * should be defined for basic type. This file implements this operation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Inverse_H_
#define _Basic_Inverse_H_

#include "type/is-float-point.h"

namespace mysimulator {

  /** @fn void _Inverse(T&)
   * @brief calculate the inverse of  input value
   *
   * For basic type, the inverse operation is implemented by dividing \a d by
   * \c 1. This resuires that \a d cannot be \c 0. To avoid the side effect
   * of generic template, a check with IsFloatPoint is used to ensure that
   * the input data is a floating-point data.
   *
   * @tparam T the type of input data
   *
   * @param d [in,out] the value to be inversed as input, the result of inverse
   *                   operation after this function
   */
  template <typename T>
  void _Inverse(T& d) {
    typedef typename IsFloatPoint<T>::Type  FloatPointCheck;
    assert(d!=0);
    d=1./d;
  }

}

#endif

