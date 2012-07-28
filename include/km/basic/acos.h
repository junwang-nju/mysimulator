
/**
 * @file basic/acos.h
 * @brief calculate ArcCosine for data of basic type
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_ArcCosine_H_
#define _Basic_ArcCosine_H_

#include <cmath>

#ifndef _ACOS
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

