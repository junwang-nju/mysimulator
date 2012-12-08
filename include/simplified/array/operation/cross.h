
#ifndef _Array_Operation_Cross_H_
#define _Array_Operation_Cross_H_

#include "array/def.h"
#include <cassert>

namespace mysimulator {

  template <typename T,ArrayKernelName K,
            typename T1,ArrayKernelName K1,typename T2,ArrayKernelName K2>
  void cross(Array<Intrinsic<T>,K>& C, Array<Intrinsic<T1>,K1> const& A,
                                       Array<Intrinsic<T2>,K2> const& B) {
    assert((bool)C);
    assert((bool)A);
    assert((bool)B);
    assert(C.size()>=3);
    assert(A.size()>=3);
    assert(B.size()>=3);
    C[0] = A[1] * B[2] - A[2] * B[1];
    C[1] = A[2] * B[0] - A[0] * B[2];
    C[2] = A[0] * B[1] - A[1] * B[0];
  }

}

#endif

