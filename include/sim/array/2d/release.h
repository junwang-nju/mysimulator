
#ifndef _Array_2D_Release_H_
#define _Array_2D_Release_H_

#include "array/1d/size.h"
#include "array/1d/refer-flag.h"

namespace mysimulator {

  template <typename T>
  void release(T**& ptr) {
    if(ptr==NULL) return;
    unsigned int n=size(ptr);
    for(unsigned int i=0;i<n;++i) assert(referFlag(ptr[i])==0);
    char *cptr;
    cptr=reinterpret_cast<char*>(ptr)-ArrayShapeShift;
    unsigned int &refFlag=*reinterpret_cast<unsigned int*>(cptr);
    if(refFlag==0) {
      char *dptr=reinterpret_cast<char*>(ptr[0])-ArrayShapeShift;
      delete[] dptr;
      delete[] cptr;
    } else --refFlag;
    ptr=NULL;
  }

}

#endif

