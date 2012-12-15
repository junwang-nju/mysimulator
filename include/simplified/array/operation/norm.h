
#ifndef _Array_Operation_Norm_H_
#define _Array_Operation_Norm_H_

#include "array/operation/dot.h"

namespace mysimulator {

  template <typename T,ArrayKernelName K>
  T NormSQ(Array<Intrinsic<T>,K,true> const& A) { return Dot(A,A); }

}

#include "basic/util/square-root.h"

namespace mysimulator {

  template <typename T,ArrayKernelName K>
  T Norm(Array<Intrinsic<T>,K,true> const& A) {
    return __square_root(Dot(A,A));
  }

}

#endif

