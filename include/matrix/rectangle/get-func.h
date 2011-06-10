
#ifndef _Matrix_Rectangle_GetFunction_H_
#define _Matrix_Rectangle_GetFunction_H_

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  T& MatrixRect_Get4C(Vector<Vector<T> >& s,
                      const unsigned int I, const unsigned int J, T* const&) {
    return s[I][J];
  }

  template <typename T>
  T& MatrixRect_Get4F(Vector<Vector<T> >& s,
                      const unsigned int I,const unsigned int J, T* const&) {
    return s[J][I];
  }

}

#endif

