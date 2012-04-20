
#ifndef _Array_2D_Compare_H_
#define _Array_2D_Compare_H_

#include "array/2d/size.h"

namespace mysimulator {

  template <typename T1, typename T2>
  bool IsSameStructure(T1** const p, T2** const q) {
    unsigned int n=size(p);
    if(n!=size(q))  return false;
    char* cpptr=reinterpret_cast<char*>(const_cast<T1**>(p))-ArrayShift;
    char* cqptr=reinterpret_cast<char*>(const_cast<T2**>(q))-ArrayShift;
    unsigned int *pidx=reinterpret_cast<unsigned int*>(cpptr)-1;
    unsigned int *qidx=reinterpret_cast<unsigned int*>(cqptr)-1;
    for(unsigned int i=0;i<n;++i) if(pidx[i]!=qidx[i])  return false;
    return true;
  }

}

#endif

