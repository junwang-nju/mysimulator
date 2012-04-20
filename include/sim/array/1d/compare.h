
#ifndef _Array_1D_Compare_H_
#define _Array_1D_Compare_H_

#include "array/1d/size.h"

namespace mysimulator {

  template <typename T1, typename T2>
  bool IsSameSize(const T1* p, const T2* q) { return size(p)==size(q); }

  template <typename T>
  bool IsSame(const T* p, const T* q) {
    unsigned int n=size(p);
    if(n!=size(q))  return false;
    if(n==0)  return true;
    n*=sizeof(T);
    const char* cp=reinterpret_cast<const char*>(p);
    const char* cq=reinterpret_cast<const char*>(q);
    for(unsigned int i=0;i<n;++i) if(cp[i]!=cq[i])  return false;
    return true;
  }

}

#endif

