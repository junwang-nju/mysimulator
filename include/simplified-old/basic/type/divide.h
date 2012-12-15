
#ifndef _Basic_Type_Divide_H_
#define _Basic_Type_Divide_H_

namespace mysimulator {

  template <typename T1,typename T2>
  class __div_flag {
    public:
      static const unsigned int FG;
  };

}

#include "basic/type/multiple.h"

namespace mysimulator {

  template <typename T1,typename T2>
  const unsigned int __div_flag<T1,T2>::FG =
      __mul_flag<T1,T2>::FG;

}

#endif

