
#ifndef _Basic_Scale_H_
#define _Basic_Scale_H_

#include "type/is-scalable.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _Scale(T1& a, const T2& b) {
    typedef typename IsScalable<T1,T2>::Type  ScaleCheck;
    a*=static_cast<T1>(b);
  }

}

#endif

