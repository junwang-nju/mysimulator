
/**
 * @file basic/imprint.h
 * @brief imprint operation for basic-type data
 *
 * To be consistent with \c ArrayNumeric object, the similar imprint operation
 * related to two data of basic type should be defined. this file implements
 * this operation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Imprint_H_
#define _Basic_Imprint_H_

#include "type/is-intrinsic.h"

namespace mysimulator {

  /** @fn void _Imprint(T&,const T&)
   * @brief imprint of one value from another value
   *
   * The imprint operation for basic type is implemented as no operation.
   * To avoid the side effect of the generic template, a check with
   * IsIntrinsic is implemented.
   *
   * @tparam T the type of concerned data
   *
   * @param a [out] the \c T -type data to be imprinted
   * @param b [in] the \c T -type data as template
   */
  template <typename T>
  void _Imprint(T& a, const T& b) {
    typedef typename IsIntrinsic<T>::Type   ImprintCheck;
  };

}

#endif

