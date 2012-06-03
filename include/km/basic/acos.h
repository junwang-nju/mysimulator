
/**
 * @file basic/acos.h
 * @brief calculate ArcCosine for data of basic type
 *
 * This is a wrapper of internal arc-cosine functions. This makes there is
 * a common interface for various input data format. Considering the
 * mathematical meaning, only floating-point data are valid as input.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_ArcCosine_H_
#define _Basic_ArcCosine_H_

#include <cmath>

#ifndef _ACOS
/** @brief the macro defining the function calculate arc-cosine
 *
 * To avoid the condition with input data is out of range (namely \a [-1,1]),
 * a comparison is used. (The input value could be slightly larger (smaller)
 * than \a 1 (\a -1) due to floating-point fluctuation.) For the normal case,
 * this calculation is implemented with \c Func.
 *
 * @param RT the type of input data
 * @param Func the funtion matching the expected data type
 */
#define _ACOS(RT,Func) \
  RT _ACos(const RT& d) { \
    if(d>1)         return static_cast<RT>(0); \
    else if(d<-1)   return static_cast<RT>(M_PI); \
    else            return Func(d); \
  }
#else
#error "Duplicate _ACOS"
#endif

namespace mysimulator {

  /** @fn double _ACos(const double&)
   * @brief definition of \a \_ACos function for \c double data
   *
   * Implemented with the macro \_ACOS
   *
   * @param d [in] the input \c double data
   * @return the angle with its cosine as the \c double data \a d
   */
  _ACOS(double, acos)
  /** @fn float _ACos(const float&)
   * @brief definition of \a \_ACos function for \c float data
   *
   * Implemented with the macro \_ACOS
   *
   * @param d [in] the input \c float data
   * @return the angle with its cosine as the \c float data \a d
   */
  _ACOS(float, acosf)
  /** @fn long double _ACos(const long double&)
   * @brief definition of \a \_ACos function for \c long \c double data
   *
   * Implemented with the macro \_ACOS
   *
   * @param d [in] the input \c long \c double data
   * @return the angle with its cosine as the \c long \c double data \a d
   */
  _ACOS(long double, acosl)

}

#ifdef _ACOS
#undef _ACOS
#endif

#endif

