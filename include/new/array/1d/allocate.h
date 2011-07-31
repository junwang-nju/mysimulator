
#ifndef _Array_1D_Allocate_H_
#define _Array_1D_Allocate_H_

#include "array/1d/interface.h"
#include "pointer/allocate.h"
#include "array/1d/content/init.h"

namespace mysimulator {

  template <typename T>
  void allocate(Array1D<T>& v, const unsigned int& n) {
    assert(n!=0);
    release(v);
    allocate(v.data,n);
    init(v,v.data(),n);
  }

  template <typename T>
  void allocate(Array1D<T>& v, const int& fst, const int& lst) {
    assert(lst>fst);
    release(v);
    unsigned int n=static_cast<unsigned int>(lst-fst+1);
    allocate(v.data,n);
    init(v,v.data(),fst,lst);
  }

}

#include "intrinsic-type/allocate.h"

namespace mysimulator {

  template <typename T>
  void imprint(Array1D<T>& v, const Array1D<T>& cv) {
    assert(IsValid(cv));
    release(v);
    allocate(v,cv.size);
    T* p=v.start;
    T* q=const_cast<T*>(cv.start);
    T* e=v.start+v.size;
    for(;p!=e;) imprint(*(p++),*(q++));
  }

}

#endif

