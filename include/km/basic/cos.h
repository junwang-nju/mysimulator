
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
 * data is \c RT -type, and the the calculation is implemented with \c Func
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

  /** @brief definition of \a _Cos function for \c double data */
  _COS(double,cos)
  /** @brief definition of \a _Cos function for \c float data */
  _COS(float,cosf)
  /** @brief definition of \a _Cos function for \c long \c double data */
  _COS(long double,cosl)

}

#ifdef _COS
#undef _COS
#endif

#endif

