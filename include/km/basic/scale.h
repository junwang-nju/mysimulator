
/**
 * @file basic/scale.h
 * @brief scale one value with another
 *
 * To be consistent with the operation for \c ArrayNumeric object, the operation
 * to scale one object with another should be defined.
 *
 * @author Jun | junwang.nju@gmail.com
 *
 * @todo some other possible scale interfaces are defined.
 */

#ifndef _Basic_Scale_H_
#define _Basic_Scale_H_

#include "type/is-scalable.h"

namespace mysimulator {

  /** @fn void _Scale(T1&, const T2&)
   * @brief scale the first value with the second
   *
   * For basic types, this operation just scales the first value with the
   * second value. To avoid the side effect of the generic template, a check
   * with IsScalable is used to check the consistency of two concerned types.
   *
   * @tparam T1 the type of data to be scaled
   * @tparam T2 the type of data as the scaling factor
   *
   * @param a [in,out] input a value, and it is scaled with \a b and the result
   *                   is used as output
   * @param b [in] the scaling factor
   */
  template <typename T1, typename T2>
  void _Scale(T1& a, const T2& b) {
    typedef typename IsScalable<T1,T2>::Type  ScaleCheck;
    a*=static_cast<T1>(b);
  }

}

#endif

