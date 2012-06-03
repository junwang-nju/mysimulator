
/**
 * @file basic/copy.h
 * @brief the copy operation for basic-type data
 *
 * To be consistent with \c ArrayNumeric object, the similar copy operation
 * between data for basic type should be defined. this file implements this
 * operation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Copy_H_
#define _Basic_Copy_H_

#include "type/is-copyable.h"

namespace mysimulator {

  /** @fn void _Copy(T1&, const T2&)
   * @brief copy operation from \c T2 -type data to \c T1 -type data
   *
   * This copy operation only works for basic types. It just assignes
   * one value to another. To avoid the side effect of the generic template,
   * a check with \c IsCopyable is implemented.
   *
   * @tparam T1 the type of destination data to be assigned
   * @tparam T2 the type of source data during copy
   *
   * @param a [out] the \c T1 -type data as the destination of copy operation
   * @param b [in] the \c T2 -type data as the source of copy operation
   */
  template <typename T1, typename T2>
  void _Copy(T1& a, const T2& b) {
    typedef typename IsCopyable<T1,T2>::Type CopyCheck;
    a=static_cast<T1>(b);
  }

  /** @fn void _Copy(bool&, const T&)
   * @brief copy operation from \c T -type data to \c bool data
   *
   * The validity of this copy operation is checked by \c IsCopyable.
   * the resultant bool is \c true when \a b is not \c 0, \c false otherwise.
   *
   * @tparam T the type of source data in copy operation
   *
   * @param a [out] the \c bool variable as the destination of copy operation
   * @param b [in] the \c T -type data as the source of copy operation
   */
  template <typename T>
  void _Copy(bool& a, const T& b) {
    typedef typename IsCopyable<bool,T>::Type CopyCheck;
    a=(b==0?false:true);
  }

}

#endif

