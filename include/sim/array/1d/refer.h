
#ifndef _Array_1D_Refer_H_
#define _Array_1D_Refer_H_

#include "array/1d/release.h"
#include "array/1d/refer-flag.h"

namespace mysimulator {

  template <typename T>
  void refer(T*& dest, const T* orig) {
    release(dest);
    dest=const_cast<T*>(orig);
    ++referFlag(dest);
  }

}

#endif

