
#ifndef _Basic_Swap_H_
#define _Basic_Swap_H_

#include "type/is-intrinsic.h"

namespace mysimulator {

  template <typename T>
  void _SwapContent(T& a, T& b) {
    typedef typename IsIntrinsic<T>::Type IntrinsicTypeCheck;
    T c;
    c=a;  a=b;  b=c;
  }

}

#endif

