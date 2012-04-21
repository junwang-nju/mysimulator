
#ifndef _Array_1D_Compare_H_
#define _Array_1D_Compare_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T1,typename T2>
  bool IsSameSize(const Array1D<T1>& V1,const Array1D<T2>& V2) {
    return V1.Size()==V2.Size();
  }

  template <typename T>
  bool IsSame(const Array1D<T>& V1,const Array1D<T>& V2) {
    unsigned int n=V1.Size();
    if(n!=V2.Size())  return false;
    if(n==0)  return true;
    const char* p1=reinterpret_cast<const char*>(V1._data);
    const char* p2=reinterpret_cast<const char*>(V2._data);
    n*=sizeof(T);
    for(unsigned int i=0;i<n;++i) if(p1[i]!=p2[i])  return false;
    return true;
  }

}

#endif

