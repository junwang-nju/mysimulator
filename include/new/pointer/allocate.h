
#ifndef _Pointer_Allocate_H_
#define _Pointer_Allocate_H_

#include "pointer/interface.h"
#include "intrinsic-type/allocate.h"
#include "intrinsic-type/release.h"

namespace mysimulator {

  template <typename T>
  void allocate(Pointer<T>& p) {
    release(p);
    allocate(p.ptr);
    p.state=0;
    p.parent=NULL;
    p.pstate=-1;
    p.delfunc=delete_pointer<T>;
  }

  template <typename T>
  void allocate(Pointer<T>& p, const unsigned int& n) {
    release(p);
    allocate(p.ptr,n);
    p.state=0;
    p.parent=NULL;
    p.pstate=-1;
    p.delfunc=delete_array<T>;
  }

}

#endif

