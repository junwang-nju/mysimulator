
#ifndef _Array_1D_IO_H_
#define _Array_1D_IO_H_

#include "array/1d/interface.h"
#include "intrinsic-type/io.h"

namespace mysimulator {

  template <typename T>
  void Write(const Array1D<T>& V) {
    assert(V.IsValid());
    Write(V[0]);
    for(unsigned int i=1;i<V.Size();++i) { Write("\t",V[i]); }
  }

}

#endif

