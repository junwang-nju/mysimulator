
#ifndef _Array_Common_Refer_H_
#define _Array_Common_Refer_H_

#include "array/common/refer-flag.h"

namespace mysimulator {

  template <typename T>
  void refer(T*& dest, const T* orig) {
    assert(dest==NULL);
    dest=const_cast<T*>(orig);
    ++referFlag(dest);
  }

}

#endif

