
#ifndef _Basic_Type_Divide_H_
#define _Basic_Type_Divide_H_

namespace mysimulator {

  template <typename T1,typename T2>
  class __div { public: static const unsigned int FLAG; };

}

#include "basic/type/multiple.h"

namespace mysimulator {

  template <typename T1,typename T2>
  const unsigned int __div<T1,T2>::FLAG =
      __mul<T1,T2>::FLAG && Intrinsic<T1>::IsFloatingPoint &&
                            Intrinsic<T2>::IsFloatingPoint;

}

#endif

