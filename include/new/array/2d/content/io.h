
#ifndef _Array_2D_Content_InputOutput_H_
#define _Array_2D_Content_InputOutput_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/io.h"

namespace mysimulator {

  template <typename T>
  OutputBase& operator<<(OutputBase& O, const Array2DContent<T>& A) {
    assert(IsValid(O)&&IsValid(A));
    for(int i=A.infra.first;i<A.infra.last;++i) O<<A[i]<<Endl;
    O<<A[A.infra.last];
    return O;
  }

  template <typename T>
  InputBase& operator>>(InputBase& I, Array2DContent<T>& A) {
    assert(IsValid(I)&&IsValid(A));
    I>>A.base;
    return I;
  }

}

#endif

