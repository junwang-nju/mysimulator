
#ifndef _Array_2D_Allocate_H_
#define _Array_2D_Allocate_H_

#include "array/1d/sum.h"
#include "array/1d/size.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <typename T>
  T** allocate(const unsigned int* sz) {
    char *p=NULL;
    T *pd=NULL;
    unsigned int n=size(sz);
    unsigned int gn=Sum(sz,n);
    pd=allocate<T>(gn);
    p=new char[ArrayShift+n*sizeof(unsigned int)+n*sizeof(T*)];
    for(int i=n-1;i>=0;--i) {
      *reinterpret_cast<unsigned int*>(p)=sz[i];
      p+=sizeof(unsigned int);
    }
    *reinterpret_cast<unsigned int*>(p+ArraySizeShift)=n;
    *reinterpret_cast<unsigned int*>(p)=0;
    T** tp=reinterpret_cast<T**>(p+ArrayShift);
    tp[0]=pd;
    for(unsigned int i=0;i<n-1;++i) tp[i+1]=tp[i]+sz[i];
    return tp;
  }

}

#endif

