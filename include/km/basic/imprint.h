
#ifndef _Basic_Imprint_H_
#define _Basic_Imprint_H_

#include "type/is-intrinsic.h"

namespace mysimulator {

  template <typename T>
  void _Imprint(T& a, const T& b) {
    typedef typename IsIntrinsic<T>::Type   ImprintCheck;
  };

}

#endif

