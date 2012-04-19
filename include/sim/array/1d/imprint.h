
#ifndef _Array_1D_Imprint_H_
#define _Array_1D_Imprint_H_

#include "array/1d/release.h"
#include "array/1d/size.h"
#include "array/1d/allocate.h"
#include "intrinsic-type/imprint.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void imprintStructure(T1*& p, const T2* q) {
    release(p);
    allocate(p,size(q));
  }

  template <typename T>
  void imprint(T*& p, const T* q) {
    release(p);
    unsigned int n=size(q);
    allocate(p,n);
    for(unsigned int i=0;i<n;++i) imprint(p[i],q[i]);
  }

}

#endif

