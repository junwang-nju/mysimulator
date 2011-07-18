
#ifndef _Intrinsic_Type_Refer_H_
#define _Intrinsic_Type_Refer_H_

#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T>
  void refer(T& d, const T& rd) {
    typedef typename _Dual<T,T>::AssignType Type;
    copy(d,rd);
  }

}

#endif

