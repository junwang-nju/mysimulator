
#ifndef _Array_2D_Compare_H_
#define _Array_2D_Compare_H_

#include "array/2d/interface.h"
#include "array/1d/compare.h"

namespace mysimulator {

  template <typename T1,typename T2>
  bool IsSameStructure(const Array1D<T1>& V1,const Array1D<T2>& V2) {
    if(!IsSameSize(V1,V2))  return false;
    for(unsigned int i=0;i<V1.Size();++i)
      if(!IsSameSize(V1[i],V2[i]))  return false;
    return true;
  }

}

#endif

