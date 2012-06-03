
/**
 * @file cos.h
 * @brief Cosine Operation (Math)
 *
 * This is a wrapper of cosine calculation. It helps to match the type of
 * input parameter. Considering the mathematical meaning, only floating-point
 * data are valid as input.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Cosine_H_
#define _Basic_Cosine_H_

#include <cmath>

/** @def _COS
 * @brief calculate cosine for \c RT -type data
 *
 * This is a macro to ease the definition of cosine funtion. The input
 * data is \c RT -type, and the calculation is implemented with \c Func
 *
 * @param RT the type of input data
 * @param Func the function matching the input data type
 */
#ifndef _COS
#define _COS(RT,Func)   RT _Cos(const RT& d) { return Func(d); }
#else
#error "Duplicate _COS"
#endif

namespace mysimulator {

  /** @fn double _Cos(const double& d)
   * @brief definition of \c \_Cos function for \c double data
   *
   * Implemented with macro \c \_COS
   *
   * @param d [in] the input \c double data (as angle)
   * @return cosine of input \c double angle
   */
  _COS(double,cos)
  /** @fn float _Cos(const float&)
   * @brief definition of \c \_Cos function for \c float data
   *
   * Implemented with macro \c \_COS
   *
   * @param d [in] the input \c float data (as angle)
   * @return cosine of input \c float angle
   */
  _COS(float,cosf)
  /** @fn long double _Cos(const long double&)
   * @brief definition of \c \_Cos function for \c long \c double data
   *
   * Implemented with macro \c \_COS
   *
   * @param d [in] the input \c long \c double data (as angle)
   * @return cosine of input \c long \c double angle
   */
  _COS(long double,cosl)

}

#ifdef _COS
#undef _COS
#endif

#endif

