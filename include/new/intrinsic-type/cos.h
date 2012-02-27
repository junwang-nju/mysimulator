
#ifndef _Intrinsic_Type_Cosine_H_
#define _Intrinsic_Type_Cosine_H_

#include <cmath>

#define _COS(type,func) type Cosine(const Type& d) { return func(d); }

namespace mysimulator {

  _COS(double,cos)
  _COS(float,cosf)
  _COS(long double,cosl)

}

#undef _COS

#endif

