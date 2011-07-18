
#ifndef _Array_1D_Allocate_H_
#define _Array_1D_Allocate_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void allocate(Array1D<T>& v, const unsigned int n) {
    assert(n!=0);
    release(v);
    v.size=n;
    allocate(static_cast<typename Array1D<T>::ParentType&>(v),v.size);
    v.first=0;
    v.last=n-1;
    v.head=v();
    v.start=v.head+v.first;
  }

  template <typename T>
  void allocate(Array1D<T>& v, const int& fst, const int& lst) {
    assert(fst<lst);
    release(v);
    v.size=static_cast<unsigned int>(lst-fst+1);
    allocate(static_cast<typename Array1D<T>::ParentType&>(v),v.size);
    v.first=fst;
    v.last=lst;
    v.head=v()-v.first;
    v.start=v.head+v.first;
  }

}

#include "intrinsic-type/allocate.h"

namespace mysimulator {

  template <typename T>
  void imprint(Array1D<T>& v, const Array1D<T>& cv) {
    assert(IsValid(cv));
    release(v);
    allocate(v,cv.first,cv.last);
    T* p=v.start;
    T* q=const_cast<T*>(cv.start);
    T* e=v.start+v.size;
    for(;p!=e;) imprint(*(p++),*(q++));
  }

}

#endif

