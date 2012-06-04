
/**
 * @file basic/shift.h
 * @brief shift operation related to basic-type data
 *
 * To be consistent with the operation for \c ArrayNumeric object, the operation
 * to shift a basic-type data should be defined. this file implements this
 * kinf of operations.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Shift_H_
#define _Basic_Shift_H_

#include "type/is-shiftable.h"

namespace mysimulator {

  /** @fn void _Shift(T&,const T1&)
   * @brief shift one value with another value
   * 
   * This is implemented by adding the factor \a b to the value \a a,
   * \f$a \leftarrow a+b \f$. To avoid side effect of generic template,
   * a check with \c IsShiftable is introduced.
   *
   * @tparam T the type of value to be shifted
   * @tparam T1 the type of data as shift step
   *
   * @param a [in,out] the value to be shifted
   * @param b [in] the data as the shift step
   */
  template <typename T, typename T1>
  void _Shift(T& a, const T1& b) {
    typedef typename IsShiftable<T,T1>::Type  ShiftCheck;
    a+=static_cast<T>(b);
  }

  /** @fn void _NegShift(T&,const T1&)
   * @brief shift one value along negative direction with another value
   *
   * This is implemented by subtracting the factor \a b from the value
   * \a a, \f$a\leftarrow a-b\f$. this operation may ease the shift operation
   * with minimal input. To avoid side effect of generic template, a check with
   * \c IsNegShiftable is introduced.
   *
   * @tparam T the type of value to be shifted
   * @tparam T1 the type of data as shift step
   *
   * @param a [in,out] the value to be shifted
   * @param b [in] the data as the shift step
   */
  template <typename T, typename T1>
  void _NegShift(T& a, const T1& b) {
    typedef typename IsNegShiftable<T,T1>::Type  NegShiftCheck;
    a-=static_cast<T>(b);
  }

  /** @fn void _Shift(T&,const T1&,const T2&)
   * @brief shift a value with the product of other two values
   *
   * This is implemented by adding the product of factors \a b and \a c to
   * the value \a a, \f$ a\leftarrow a+b\times c\f$. to avoid the side effect 
   * of generic template, a check with \c IsShiftable3 is introduced.
   *
   * @tparam T the type of value to be shifted
   * @tparam T1,T2 the types of data related to shift steps
   *
   * @param a [in,out] the value to be shifted
   * @param b,c [in] two factors defining the shift step
   */
  template <typename T,typename T1,typename T2>
  void _Shift(T& a, const T1& b, const T2& c) {
    typedef typename IsShiftable3<T,T1,T2>::Type  ShiftCheck;
    a+=static_cast<T>(b)*static_cast<T>(c);
  }

  /** @fn void _Shift(T&,const T1&,const T2&,const T3&)
   * @brief shift a value with product of three values
   *
   * THis is implemented by adding the product of factors \a b, \a c, and
   * \a d to the value \a a, \f$a\leftarrow a+b\times c\times d\f$. to avoid
   * side effect of generic template, a check with \c IsShiftable4 is
   * introduced.
   *
   * @tparam T the type of value to be shifted
   * @tparam T1,T2,T3 the types of data related to shift steps
   *
   * @param a [in,out] the value to be shifted
   * @param b,c,d [in] three factors defining the shift step
   */
  template <typename T,typename T1,typename T2,typename T3>
  void _Shift(T& a, const T1& b, const T2& c, const T3& d) {
    typedef typename IsShiftable4<T,T1,T2,T3>::Type ShiftCheck;
    a+=static_cast<T>(b)*static_cast<T>(c)*static_cast<T>(d);
  }

}

#endif

