
#ifndef _Basic_Scale_H_
#define _Basic_Scale_H_

#include "type-check/is-scalable.h"
#include "type-check/is-numeric.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _Scale(T1& a, const T2& b) {
    typedef typename IsScalable<T1,T2>::Type  ScaleCheck;
    typedef typename IsNumeric<T1>::Type      NumericCheck1;
    typedef typename IsNumeric<T2>::Type      NumericCheck2;
    a*=b;
  }

}

#endif

