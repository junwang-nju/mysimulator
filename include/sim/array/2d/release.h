
#ifndef _Array_2D_Release_H_
#define _Array_2D_Release_H_

#include "array/1d/release.h"
#include "array/common/refer-flag.h"

namespace mysimulator {

  template <typename T>
  void release2d(T**& ptr) {
    if(ptr==NULL) return;
    if(referFlag(ptr)==0) {
      release(*ptr);
      unsigned int n=size(ptr);
      char* cptr=reinterpret_cast<char*>(ptr)-ArrayShift-n*sizeof(unsigned int);
      delete[] cptr;
    }
    else --referFlag(ptr);
    ptr=NULL;
  }

}

#endif

