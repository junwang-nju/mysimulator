
/**
 * @file basic/square-root.h
 * @brief calculate square root for data of basic type
 *
 * This is a wrapper to calculate square root. It helps to match the type of
 * input parameter. Considering the mathematical meaning, only floating-point
 * data are valid as input.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_SquareRoot_H_
#define _Basic_SquareRoot_H_

#include <cmath>

/** @def _SQROOT_
 * @brief calculate square root for \c T -type data
 *
 * This is a macro to ease the definition of square-root function. The input
 * data is \c T -type, and the calculation is implemented with \c Func.
 *
 * @param T the type of the input data
 * @param Func the function matching the input data type
 */
#ifndef _SQROOT_
#define _SQROOT_(T,Func)  T __SqRoot(const T& d) { return Func(d); }
#else
#error "Duplicate _SQROOT_"
#endif

namespace mysimulator {

  /** @fn long double __SqRoot(const long double&)
   * @brief definition of \c \_\_SqRoot function for \c long \c double data
   *
   * Implemented with macro \c \_SQROOT\_
   *
   * @param d [in] the input \c long \c double data
   * @return the square root of input \c long \c double data
   * @note \a d should be larger than \c 0
   */
  _SQROOT_(long double, sqrtl)
  /** @fn double __SqRoot(const double&)
   * @brief definition of \c \_\_SqRoot function for \c double data
   *
   * Implemented with macro \c \_SQROOT\_
   *
   * @param d [in] the input \c double data
   * @return the square root of input \c double data
   * @note \a d should be larger than \c 0
   */
  _SQROOT_(double,      sqrt)
  /** @fn float __SqRoot(const float&)
   * @brief definition of \c \_\_SqRoot function for \c float data
   *
   * Implemented with macro \c \_SQROOT\_
   *
   * @param d [in] the input \c float data
   * @return the square root of input \c float data
   * @note \a d should be larger than \c 0
   */
  _SQROOT_(float,       sqrtf)

}

#ifdef _SQROOT_
#undef _SQROOT_
#endif

#include "type/is-float-point.h"

namespace mysimulator {

  /** @fn void _SqRoot(T&)
   * @brief calculate square root for \c T -type data
   *
   * This function calculates square root of input data. The purpose of
   * this function is to enable the check for the type of input data.
   * It is implemented with the functions \c \_\_SqRoot. To be consistent
   * with the interface for other objects (such as ArrayNumeric), the
   * function operates the input object, rather than return a value.
   *
   * @tparam T the type of input data
   * @param d [in,out] the object storing input data and output result
   */
  template <typename T>
  void _SqRoot(T& d) {
    typedef typename IsFloatPoint<T>::Type  FloatPointCheck;
    d=__SqRoot(d);
  }

}

#endif

