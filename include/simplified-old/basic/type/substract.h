
#ifndef _Basic_Type_Substract_H_
#define _Basic_Type_Substract_H_

namespace mysimulator {

  template <typename T1,typename T2>
  class __sub_flag {
    public:
      static const unsigned int FG;
  };

}

#include "basic/type/sum.h"

namespace mysimulator {

  template <typename T1,typename T2>
  const unsigned int __sub_flag<T1,T2>::FG=__sum_flag<T1,T2>::FG;

}

#endif

