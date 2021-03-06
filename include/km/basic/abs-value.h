
/**
 * @file basic/abs-value.h
 * @brief calculate absolute value for data of basic type
 *
 * this module calculates the absolute value of data of intrinsic type.
 * this is a basic mathematical operation for various kinds of sign numbers.
 * These functions unify the interface for vatious types of numbers.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_AbsoluteValue_H_
#define _Basic_AbsoluteValue_H_

#include <cmath>
#include <cstdlib>

/** @def _AbsValDEF_
 * @brief calculate absolute value with pre-defined method
 *
 * For some data types (including float-pointer data, and \c long \c long,
 * \c long, and \c int), there are some pre-defined methods. This macro
 * implements a unique interface to calculate absolute value of the input
 * data with these pre-defined data.
 *
 * @param T the type of input data
 * @param Func the function to carry out the calculation
 */
#ifndef _AbsValDEF_
#define _AbsValDEF_(T,Func)  T AbsVal(const T& d) { return Func(d); }
#else
#error "Duplicate _AbsValDEF_"
#endif

namespace mysimulator {

  /** @fn long double AbsVal(const long double&)
   * @brief get absolute value of \c long \c double data
   *
   * Implemented with the macro \c \_AbsValDEF\_
   *
   * @param d [in] the input \c long \c double data
   * @return the absolute value of input \c long \c double data
   */
  _AbsValDEF_(long double,fabsl)
  /** @fn double AbsVal(const double&)
   * @brief get absolute value of \c double data
   *
   * Implemented with the macro \c \_AbsValDEF\_
   *
   * @param d [in] the input \c double data
   * @return the absolute value of input \c double data
   */
  _AbsValDEF_(double,fabs)
  /** @fn float AbsVal(const float&)
   * @brief get absolute value of \c float data
   *
   * Implemented with the macro \c \_AbsValDEF\_
   *
   * @param d [in] the input \c float data
   * @return the absolute value of input \c float data
   */
  _AbsValDEF_(float,fabsf)
  /** @fn long long AbsVal(const long long&)
   * @brief get absolute value of \c long \c long data
   *
   * Implemented with the macro \c \_AbsValDEF\_
   *
   * @param d [in] the input \c long \c long data
   * @return the absolute value of input \c long \c long data
   */
  _AbsValDEF_(long long,llabs)
  /** @fn int AbsVal(const int&)
   * @brief get absolute value of \c int data
   *
   * Implemented with the macro \c \_AbsValDEF\_
   *
   * @param d [in] the input \c int data
   * @return the absolute value of input \c int data
   */
  _AbsValDEF_(int,abs)
  /** @fn long AbsVal(const long&)
   * @brief get absolute value of \c long data
   *
   * Implemented with the macro \c \_AbsValDEF\_
   *
   * @param d [in] the input \c long data
   * @return the absolute value of input \c long data
   */
  _AbsValDEF_(long,labs)

}

#ifdef _AbsValDEF_
#undef _AbsValDEF_
#endif

/** @def _AbsValDEF1_
 * @brief calculate absolute value with comparison
 *
 * For some data types (such as char and short), there are no pre-defined
 * methods to calculate absolute values. The calculation is implemented
 * by comparing the value with zero.
 *
 * @param T the type of input data
 */
#ifndef _AbsValDEF1_
#define _AbsValDEF1_(T) T AbsVal(const T& d) { return d>0?d:-d; }
#else
#error "Duplicate _AbsValDEF1_"
#endif

namespace mysimulator {

  /** @fn short AbsVal(const short&)
   * @brief get absolute value of \c short data
   *
   * Implemented with the macro \c \_AbsValDEF1\_
   *
   * @param d [in] the input \c short data
   * @return the absolute value of input \c short data
   */
  _AbsValDEF1_(short)
  /** @fn char AbsVal(const char&)
   * @brief get absolute value of \c char data
   *
   * Implemented with the macro \c \_AbsValDEF1\_
   *
   * @param d [in] the input \c char data
   * @return the absolute value of input \c char data
   */
  _AbsValDEF1_(char)

}

#ifdef _AbsValDEF1_
#undef _AbsValDEF1_
#endif

/** def _AbsValDEF2_
 * @brief calculate absolute value for unsigned value
 *
 * the absolute value of unsigned number is itself.
 *
 * @param T the type of input data
 */
#ifndef _AbsValDEF2_
#define _AbsValDEF2_(T) T AbsVal(const T& d) { return d; }
#else
#error "Duplicate _AbsValDEF2_"
#endif

namespace mysimulator {

  /** @fn unsigned long long AbsVal(const unsigned long long&)
   * @brief get absolute value of \c unsigned \c long \c long data
   *
   * Implemented with the macro \c \_AbsValDEF2\_
   *
   * @param d [in] the input \c unsigned \c long \c long data
   * @return the absolute value of input \c unsigned \c long \c long data
   */
  _AbsValDEF2_(unsigned long long)
  /** @fn unsigned int AbsVal(const unsigned int&)
   * @brief get absolute value of \c unsigned \c int data
   *
   * Implemented with the macro \c \_AbsValDEF2\_
   *
   * @param d [in] the input \c unsigned \c int data
   * @return the absolute value of input \c unsigned \c int data
   */
  _AbsValDEF2_(unsigned int)
  /** @fn unsigned long AbsVal(const unsigned long&)
   * @brief get absolute value of \c unsigned \c long data
   *
   * Implemented with the macro \c \_AbsValDEF2\_
   *
   * @param d [in] the input \c unsigned \c long data
   * @return the absolute value of input \c unsigned \c long data
   */
  _AbsValDEF2_(unsigned long)
  /** @fn unsigned short AbsVal(const unsigned short&)
   * @brief get absolute value of \c unsigned \c short data
   *
   * Implemented with the macro \c \_AbsValDEF2\_
   *
   * @param d [in] the input \c unsigned \c short data
   * @return the absolute value of input \c unsigned \c short data
   */
  _AbsValDEF2_(unsigned short)
  /** @fn unsigned char AbsVal(const unsigned char&)
   * @brief get absolute value of \c unsigned \c char data
   *
   * Implemented with the macro \c \_AbsValDEF2\_
   *
   * @param d [in] the input \c unsigned \c char data
   * @return the absolute value of input \c unsigned \c char data
   */
  _AbsValDEF2_(unsigned char)

}

#ifdef _AbsValDEF2_
#undef _AbsValDEF2_
#endif

#endif

