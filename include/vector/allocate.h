
#ifndef _Vector_Allocate_H_
#define _Vector_Allocate_H_

#include "vector/interface.h"
#include "intrinsic-type/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(Vector<T>& v, const unsigned int n) {
    assert(n>0);
    release(v);
    v.pdata=new T[n];
    v.size=n;
    v.state=AllocatedVector;
  }
  template <typename T>
  void imprint(Vector<T>& v, const Vector<T>& cv) {
    assert(IsValid(cv));
    release(v);
    allocate(v,cv.size);
    for(unsigned int i=0;i<v.size;++i) imprint(v[i],cv[i]);
  }

}

#endif

