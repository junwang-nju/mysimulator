
#ifndef _Generic_Copy_H_
#define _Generic_Copy_H_

#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T>
  void copy(void*& ptr, const T* tptr) {
    assert(IsValid(tptr));
    ptr=reinterpret_cast<void*>(const_cast<T*>(tptr));
  }
  template <typename T>
  void copy(T*& tptr, const void* ptr) {
    assert(IsValid(ptr));
    tptr=reinterpret_cast<T*>(const_cast<void*>(ptr));
  }
  template <typename T>
  void copy(T*& ptr, T* const& tptr) {
    assert(IsValid(tptr));
    ptr=const_cast<T*>(tptr);
  }

}

#endif

