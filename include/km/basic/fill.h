
#ifndef _Basic_Fill_H_
#define _Basic_Fill_H_

#include "type/is-fillable.h"
#include "basic/copy.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _Fill(T1& a, const T2& b) {
    typedef typename IsFillable<T1,T2>::Type  FillCheck;
    _Copy(a,b);
  }

}

#endif

