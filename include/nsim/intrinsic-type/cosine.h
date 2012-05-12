
#ifndef _Interaction_Type_Cosine_H_
#define _Interaction_Type_Cosine_H_

#include <cmath>

#ifndef _COS
#define _COS(T,Func) T Cosine(const T& d) { return Func(d); }
#else
#error "Duplicate Definition for Maco _COS"
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

