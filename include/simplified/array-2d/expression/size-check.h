
#ifndef _Array_2D_Expression_Size_Check_H_
#define _Array_2D_Expression_Size_Check_H_

#include "array/expression/size-check.h"

namespace mysimulator {

  template <typename EA,typename EB>
  bool __is_expression_size_same(EA const& A, EB const& B) {
    if(A.size()!=B.size())  return false;
    for(unsigned int i=0;i<A.size();++i)
      if(!__is_expression_size_same(A[i],B[i])) return false;
    return true;
  }

}

#endif

