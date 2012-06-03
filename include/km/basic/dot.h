
/**
 * @file basic/dot.h
 * @brief dot produce for basic-type data
 *
 * To be consistent with ArrayNumeric object, the similar operation to
 * calculate the dot product of two basic-type values should be introduced.
 * this file implements this operation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Dot_H_
#define _Basic_Dot_H_

#include "type/combine.h"
#include "type/is-numeric.h"

namespace mysimulator {

  /** @fn typename CombineType<T1,T2>::Type _Dot(const T1&,const T2&)
   * @brief dot product of \c T1 -type and \c T2 -type data
   *
   * The dot produt of two basic-type value is defined as their product.
   * To avoid side effect of the generic template, a check with \c IsNumeric
   * is implemented. The type of output is derived with \c CombineType.
   *
   * @tparam T1,T2 the types of input data
   *
   * @param a [in] the \c T1 -type data
   * @param b [in] the \c T2 -type data
   * @return the dot product of input data
   */
  template <typename T1, typename T2>
  typename CombineType<T1,T2>::Type
  _Dot(const T1& a, const T2& b) {
    typedef typename IsNumeric<T1>::Type  DotCheck1;
    typedef typename IsNumeric<T2>::Type  DotCheck2;
    typedef typename CombineType<T1,T2>::Type DType;
    return static_cast<DType>(a)*static_cast<DType>(b);
  }

}

#endif

