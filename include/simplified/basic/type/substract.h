
#ifndef _Basic_Type_Substract_H_
#define _Basic_Type_Substract_H_

namespace mysimulator {

  template <typename T1,typename T2>
  class __sub { public: static const unsigned int FLAG; };

}

#include "basic/type/sum.h"

namespace mysimulator {

  template <typename T1,typename T2>
  const unsigned int __sub<T1,T2>::FLAG = __sum<T1,T2>::FLAG;

}

#endif

