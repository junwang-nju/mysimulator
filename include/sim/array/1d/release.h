
#ifndef _Array_1D_Release_H_
#define _Array_1D_Release_H_

#include "array/common/shape-parameter.h"
#include <cstdlib>

namespace mysimulator {

  template <typename T>
  void release(T* &ptr) {
    if(ptr==NULL) return;
    char* cptr=reinterpret_cast<char*>(ptr)-ArrayShapeShift;
    unsigned int &refFlag=*reinterpret_cast<unsigned int*>(cptr);
    if(refFlag==0)  delete[] cptr;
    else --refFlag;
    ptr=NULL;
  }

}

#endif

