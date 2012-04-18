
#ifndef _Array_1D_Allocate_H_
#define _Array_1D_Allocate_H_

#include "array/common/shape.h"
#include <cstdlib>

namespace mysimulator {

  template <typename T>
  T* allocate(const unsigned int& n) {
    char* ptr=NULL;
    ptr=new char[sizeof(T)*n+ArrayShift];
    *reinterpret_cast<unsigned int*>(ptr+ArraySizeShift)=n;
    *reinterpret_cast<unsigned int*>(ptr)=0;
    return reinterpret_cast<T*>(ptr+ArrayShift);
  }

}

#endif

