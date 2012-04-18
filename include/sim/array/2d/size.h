
#ifndef _Array_2D_Size_H_
#define _Array_2D_Size_H_

#include "array/1d/size.h"

namespace mysimulator {

  template <typename T>
  unsigned int linesize(T** const p, const unsigned int n) {
    assert(n<=size(p));
    char* cptr=reinterpret_cast<char*>(const_cast<T**>(p))-ArrayShift;
    return *(reinterpret_cast<unsigned int*>(cptr)-n-1);
  }

}

#endif

