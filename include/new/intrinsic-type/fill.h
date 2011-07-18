
#ifndef _Intrinsic_Type_Fill_H_
#define _Intrinsic_Type_Fill_H_

#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T, typename fT>
  void fill(T& a, const fT& b) {
    typedef typename _Dual<T,fT>::AssignType  Type;
    copy(a,b);
  }

}

#endif

