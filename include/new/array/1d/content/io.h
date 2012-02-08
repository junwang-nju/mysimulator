
#ifndef _Array_1D_Content_InputOutput_H_
#define _Array_1D_Content_InputOutput_H_

#include "array/1d/content/interface.h"
#include "io/output/base/interface.h"

namespace mysimulator {

  template <typename T>
  OutputBase& operator<<(OutputBase& O, const Array1DContent<T>& A) {
    assert(IsValid(O)&&IsValid(A));
    for(int i=A.first;i<A.last;++i)  O<<A[i]<<"\t";
    O<<A[A.last];
    return O;
  }

  OutputBase& operator<<(OutputBase& O, const Array1DContent<char>& A) {
    assert(IsValid(O)&&IsValid(A));
    for(int i=A.first;i<=A.last;++i)  O<<A[i];
    return O;
  }

}

#include "io/input/base/interface.h"

namespace mysimulator {

  template <typename T>
  InputBase& operator>>(InputBase& I, Array1DContent<T>& A) {
    assert(IsValid(I)&&IsValid(A));
    for(int i=A.first;i<=A.last;++i)  I>>A[i];
    return I;
  }

}

#endif

