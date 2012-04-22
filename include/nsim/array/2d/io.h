
#ifndef _Array_2D_IO_H_
#define _Array_2D_IO_H_

#include "array/2d/interface.h"
#include "array/1d/io.h"

namespace mysimulator {

  template <typename T>
  void Write(const Array2D<T>& V) {
    assert(V.IsValid());
    Write(V[0]);
    for(unsigned int i=1;i<V.Size();++i)  Write("\n",V[i]);
  }

}

#endif

