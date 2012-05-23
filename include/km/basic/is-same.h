
#ifndef _Basic_IsSame_H_
#define _Basic_IsSame_H_

#include "type/is-intrinsic.h"

namespace mysimulator {

  template <typename T>
  bool IsSame(const T& A, const T& B) {
    typedef typename IsIntrinsic<T>::Type   Type;
    return A==B;
  }

}

#endif

