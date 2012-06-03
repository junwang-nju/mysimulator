
/**
 * @file basic/fill.h
 * @brief fill operation for basic-type data
 *
 * To be consistent with \c ArrayNumeric object, the similar fill operation
 * between data for basic type should be defined. this file implements this
 * operation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Fill_H_
#define _Basic_Fill_H_

#include "type/is-fillable.h"
#include "basic/copy.h"

namespace mysimulator {

  /** @fn void _Fill(T1&, const T2&);
   * @brief fill operation of \c T1 -type data with \c T2 -type data
   *
   * This is implemented with _Copy for basic type. To avoid the side effect
   * of the generic template, a check with IsFillable is implemented.
   *
   * @tparam T1 the type of data to be filled
   * @tparam T2 the type of data used to fill
   *
   * @param a [out] the data to be filled
   * @param b [in] the data used to fill
   */
  template <typename T1, typename T2>
  void _Fill(T1& a, const T2& b) {
    typedef typename IsFillable<T1,T2>::Type  FillCheck;
    _Copy(a,b);
  }

}

#endif

