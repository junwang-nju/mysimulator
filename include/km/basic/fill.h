
#ifndef _Basic_Fill_H_
#define _Basic_Fill_H_

#include "type-check/is-numeric.h"
#include "basic/copy.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _Fill(T1& a, const T2& b) {
    typedef typename IsNumeric<T1>::Type  NumericCheck1;
    typedef typename IsNumeric<T2>::Type  NumericCheck2;
    _Copy(a,b);
  }

}

#endif

