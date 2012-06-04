
/**
 * @file basic/swap.h
 * @brief swap contents of two basic-type data
 *
 * to swap content of two variables is a regular operation. this operation
 * may ease the naming procedure in some algorithms. To be consisitent
 * with the operation for \c ArrayNumric object, the swap operation for
 * two values should be defined. This file implements this operation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Swap_H_
#define _Basic_Swap_H_

#include "type/is-intrinsic.h"

namespace mysimulator {

  /** @fn void _SwapContent(T&,T&)
   * @brief swap the content of two \c T -type values
   *
   * This operation is implemented by swap the values of two concerned
   * variables with a temporary variable defined. To avoid side effect
   * of generic template, a check with IsIntrinsic is used.
   *
   * @tparam T the type of data to be swapped
   *
   * @param a,b [in,out] two variables to be swapped
   * @note to be simple, two variables are assumed to be of same type
   */
  template <typename T>
  void _SwapContent(T& a, T& b) {
    typedef typename IsIntrinsic<T>::Type IntrinsicTypeCheck;
    T c;
    c=a;  a=b;  b=c;
  }

}

#endif

