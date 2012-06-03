
/**
 * @file basic/tanh.h
 * @brief calculate hyperbolic tangent function (Math)
 *
 * This is a wrapper of hyperbolic tangent function,
 * \f$(e^x-e^{-x})/(e^x+e^{-x})\f$. It helps to match the
 * type of the input parameter. Considering the mathematical meaning, only
 * floating-point data are valid as input.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Tanh_H_
#define _Basic_Tanh_H_

#include <cmath>

/** @def _TANH_
 * @brief calculate hyperbolic tangent for \c RT -type data
 *
 * This is a macro to ease the definition of hyperbolic tangent function. The
 * input data is \c RT -type, and the calculation is implemented with
 * \c Func.
 *
 * @param RT the type of input data
 * @param Func the function matching the input data type
 */
#ifndef _TANH_
#define _TANH_(RT,Func) RT _Tanh(const RT& d) { return Func(d); }
#else
#error "Duplicate _TANH_"
#endif

namespace mysimulator {

  /** @fn double _Tanh(const double& d)
   * @brief calculate hyperbolic tangent for \c double data
   *
   * Implemented with macro \c _TANH_
   *
   * @param d [in] the input \c double data
   * @return hyperbolic tangent of \c double data 
   */
  _TANH_(double,tanh)
  /** @fn float _Tanh(const float& d)
   * @brief calculate hyperbolic tangent for \c float data
   *
   * Implemented with macro \c _TANH_
   *
   * @param d [in] the input \c float data
   * @return hyperbolic tangent of \c float data 
   */
  _TANH_(float,tanhf)
  /** @fn long double _Tanh(const long double& d)
   * @brief calculate hyperbolic tangent for \c long \c double data
   *
   * Implemented with macro \c _TANH_
   *
   * @param d [in] the input \c long \c double data
   * @return hyperbolic tangent of \c long \c double data 
   */
  _TANH_(long double,tanhl)

}

#ifdef _TANH_
#undef _TANH_
#endif

#endif

