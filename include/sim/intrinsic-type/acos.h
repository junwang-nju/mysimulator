
#ifndef _Intrinsic_Type_ArcCosine_H_
#define _Intrinsic_Type_ArcCosine_H_

#include <cmath>

#define _ACOS(type,func) \
  type arcCos(const type& d) {\
    if(d>1)        return static_cast<type>(0); \
    else if(d<-1)  return static_cast<type>(M_PI); \
    else           return func(d);\
  }

namespace mysimulator {

  _ACOS(double,acos)
  _ACOS(float,acosf)
  _ACOS(long double,acosl)

}

#undef _ACOS

#endif

