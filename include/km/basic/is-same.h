
/**
 * @file basic/is-same.h
 * @brief check if two values are same
 *
 * To be consistent with operations for \c ArrayNumeric object, the operation
 * to judge if two values are the same should be defined. This function
 * implements this operation.
 *
 * @author Jun | junwang.nju@gmail.com
 *
 * @todo for the float-point data, the direct equality comparison may not
 *       be suitable since the finite size of word and some intrinsic nature
 *       of floating-point data. This should be defined separately.
 */

#ifndef _Basic_IsSame_H_
#define _Basic_IsSame_H_

#include "type/is-intrinsic.h"

namespace mysimulator {

  /** @fn bool IsSame(const T&,const T&)
   * @brief check if two values are the same
   *
   * It is implemented with simple equal comparison. To avoid side effect of
   * the generic template, a check with \c IsIntrinsic is used.
   *
   * @tparam T the type of the compared data
   *
   * @param A,B [in] two values to be compared
   * @return \c true when two values are the same, \c false otherwise
   *
   * @note To avoid ambiguity, only the data with a same type are compared here.
   */
  template <typename T>
  bool IsSame(const T& A, const T& B) {
    typedef typename IsIntrinsic<T>::Type   Type;
    return A==B;
  }

}

#endif

