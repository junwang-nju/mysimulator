
/**
 * @file basic/sin.h
 * @brief calculate sine for data of basic type (Math)
 *
 * This is a wrapper of sine calculation. It helps to match the type of input
 * parameter. Considering the mathematical meaning, only floating-point
 * data are valid as input.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Sine_H_
#define _Basic_Sine_H_

#include <cmath>

/** @def _SIN
 * @brief calculation sine for \c RT -type data
 *
 * This is a macro to ease the definition of sine function. The input data
 * is \c RT -type, anf the calculation is implemented with \c Func.
 *
 * @param RT the type of input data
 * @param Func the function matching the input data type
 */
#ifndef _SIN
#define _SIN(RT,Func) RT _Sin(const RT& d) { return Func(d); }
#else
#error "Duplicate _SIN"
#endif

namespace mysimulator {

  /** @fn double _Sin(const double&)
   * @brief definition of \a _Sin function for \c double data
   *
   * Implemented with the macro _SIN
   *
   * @param d [in] the input \c double data (angle)
   * @return sine of the input \c double angle
   */
  _SIN(double,sin)
  /** @fn float _Sin(const float&)
   * @brief definition of \a _Sin function for \c float data
   *
   * Implemented with the macro _SIN
   *
   * @param d [in] the input \c float data (angle)
   * @return sine of the input \c float angle
   */
  _SIN(float,sinf)
  /** @fn long double _Sin(const long double&)
   * @brief definition of \a _Sin function for \c long \c double data
   *
   * Implemented with the macro _SIN
   *
   * @param d [in] the input \c long \c double data (angle)
   * @return sine of the input \c long \c double angle
   */
  _SIN(long double,sinl)

}

#ifdef _SIN
#undef _SIN
#endif

#endif

