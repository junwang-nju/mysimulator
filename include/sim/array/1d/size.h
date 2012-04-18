
#ifndef _Array_1D_Size_H_
#define _Array_1D_Size_H_

#include "array/common/shape.h"
#include <cstdlib>

namespace mysimulator {

  template <typename T>
  unsigned int size(const T* ptr) {
    if(ptr==NULL)   return 0;
    const char* cptr=reinterpret_cast<const char*>(ptr);
    return *reinterpret_cast<const unsigned int*>(cptr-ArrayBackSizeShift);
  }

}

#endif

