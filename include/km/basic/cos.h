
#ifndef _Basic_Cosine_H_
#define _Basic_Cosine_H_

#include <cmath>

#ifndef _COS
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

