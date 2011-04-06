
#ifndef _Generic_Release_H_
#define _Generic_Release_H_

#include "intrinsic-type/validity-check.h"

namespace mysimulator {

  template <typename T>
  void release(T*& ptr) {
    if(!IsValid(ptr)) return;
    delete ptr;
    ptr=NULL;
  }

  template <typename T>
  void releaseArray(T*& ptr) {
    if(!IsValid(ptr)) return;
    delete[] ptr;
    ptr=NULL;
  }

}

#endif

