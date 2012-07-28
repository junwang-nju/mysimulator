
/**
 * @file basic/acos.h
 * @brief calculate ArcCosine for data of basic type
 *
 * This is a wrapper of internal arc-cosine functions. This makes there is
 * a common interface for various input data format.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_ArcCosine_H_
#define _Basic_ArcCosine_H_

#include <cmath>

#ifndef _ACOS
/** @brief the macro defining the function calculate arc-cosine
 *
 * To avoid the condition with input data is out of range (namely [-1,1]),
 * a comparison is used. (The input value could be slightly larger (smaller)
 * than 1 (-1) due to floating-point fluctuation.) For the normal case,
 * this calculation is implemented with Func.
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

  _ACOS(double, acos)
  _ACOS(float, acosf)
  _ACOS(long double, acosl)

}

#ifdef _ACOS
#undef _ACOS
#endif

#endif

