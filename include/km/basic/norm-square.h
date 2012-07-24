
/**
 * @file basic/norm-square.h"
 * @brief calculate square for data of basic type
 *
 * To be consistent with the operations for \c ArryNumeric object, the operation
 * to calculate the square for basic type should be defined. This file
 * implements this operation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_NormSquare_H_
#define _Basic_NormSquare_H_

#include "type/is-numeric.h"

namespace mysimulator {

  /** @fn T _NormSQ(const T&)
   * @brief calculate the square of the input value
   *
   * for basic type, this operation is just implimented as self-multiplication
   * of the input calue. To avoid side effect of the generic template, a check
   * with \c IsNumeric is used to ensure the input is a number.
   *
   * @tparam T the type of the input and output data
   *
   * @param v [in] the input value
   * @return the square of the input value
   *
   * @note The name of this function is not clear for user when facing with
   *       basic-type values. It is better to implement it similar to that
   *       for square root
   */
  template <typename T>
  T _NormSQ(const T& v) {
    typedef typename IsNumeric<T>::Type NormSQCheck;
    return v*v;
  }

}

#endif

