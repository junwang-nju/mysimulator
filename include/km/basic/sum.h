
/**
 * @file basic/sum.h
 * @brief calculate summation of data with basic type
 *
 * To be consistent with the operation for \c ArrayNumeric object, 
 * the summation operation for basic-type data should be defined. this file
 * implements this operation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Sum_H_
#define _Basic_Sum_H_

#include "type/is-numeric.h"

namespace mysimulator {

  /** @fn T _Sum(const T&)
   * @brief summation of \c T -type data
   *
   * For basic-type data, the summation is simply the orginal data. This
   * function is used to provide a consistent interface as that for
   * \c ArrayNumeric object. To avoid side effect of generic template,
   * a check with IsNumeric is used.
   *
   * @tparam T the type of data to carry out this operation
   *
   * @param v [in] the data to be summed
   * @return the input value
   */
  template <typename T>
  T _Sum(const T& v) {
    typedef typename IsNumeric<T>::Type   SumCheck;
    return v;
  }

}

#endif

