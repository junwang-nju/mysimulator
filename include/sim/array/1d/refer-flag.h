
#ifndef _Array_1D_Refer_Flag_H_
#define _Array_1D_Refer_Flag_H_

#include "array/common/shape-parameter.h"
#include <cstdlib>
#include <cassert>

namespace mysimulator {

  template <typename T>
  const unsigned int referFlag(const T* ptr) {
    if(ptr==NULL)  return 0;
    char* cptr=reinterpret_cast<const char*>(ptr)-ArrayShapeShift;
    return *reinterpret_cast<const unsigned int*>(cptr);
  }

  template <typename T>
  unsigned int& referFlag(T* ptr) {
    assert(ptr!=NULL);
    char* cptr=reinterpret_cast<char*>(ptr)-ArrayShapeShift;
    return *reinterpret_cast<unsigned int*>(cptr);
  }

}

#endif

