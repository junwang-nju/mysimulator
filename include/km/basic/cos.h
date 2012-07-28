
/**
 * @file cos.h
 * @brief Cosine Operation (Math)
 *
 * This is a wrapper of cosine calculation. It helps to match the type of
 * input parameter.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Cosine_H_
#define _Basic_Cosine_H_

#include <cmath>

#ifndef _COS
/** @brief calculate cosine for RT-type data
 *
 * This is a macro to ease the definition of cosine funtion. The input
 * data is RT-type, and the the calculation is implemented with Func
 *
 * @param RT the type of input data
 * @param Func the function matching the input data type
 */
#define _COS(RT,Func)   RT _Cos(const RT& d) { return Func(d); }
#else
#error "Duplicate _COS"
#endif

namespace mysimulator {

  _COS(double,cos)
  _COS(float,cosf)
  _COS(long double,cosl)

}

#ifdef _COS
#undef _COS
#endif

#endif

