
#ifndef _Array_2D_Content_Compare_H_
#define _Array_2D_Content_Compare_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/compare.h"

namespace mysimulator {

  template <typename T1, typename T2>
  bool IsSameSize(const Array2DContent<T1>& A1, const Array2DContent<T2>& A2) {
    if(!IsSameSize(A1.base,A2.base))    return false;
    if(!IsSameSize(A1.infra,A2.infra))  return false;
    for(int i=A1.infra.first;i<=A2.infra.last;++i)
      if(!IsSameSize(A1[i],A2[i]))  return false;
    return true;
  }

}

#endif

