
#ifndef _Array_2D_Allocate_H_
#define _Array_2D_Allocate_H_

#include "array/1d/sum.h"

namespace mysimulator {

  template <typename T>
  T** allocate(const unsigned int* sz) {
    char *p=NULL,*pd=NULL;
    unsigned int n=size(sz);
    pd=new char[n*ArrayShapeShift+Sum(sz)*sizeof(T)];
    p=new char[ArrayShapeShift+n*sizeof(T*)];
    *reinterpret_cast<unsigned int*>(p+ArrayShapeSizeShift)=n;
    *reinterpret_cast<unsigned int*>(p)=0;
    T** tp=reinterpret_cast<T**>(p+ArrayShapeShift);
    for(unsigned int i=0;i<n;++i) {
      *reinterpret_cast<unsigned int*>(pd+ArrayShapeSizeShift)=sz[i];
      *reinterpret_cast<unsigned int*>(pd)=0;
      pd+=ArrayShapeShift;
      tp[i]=reinterpret_cast<T*>(pd);
      pd+=sz[i]*sizeof(T);
    }
    return tp;
  }

}

#endif

