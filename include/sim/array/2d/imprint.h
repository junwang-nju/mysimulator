
#ifndef _Array_2D_Imprint_H_
#define _Array_2D_Imprint_H_

#include "array/2d/release.h"
#include "array/1d/imprint.h"
#include "array/1d/copy.h"

namespace mysimulator {

  template <typename T>
  void imprint(T**&p, const T** q) {
    release2d(p);
    unsigned int n=size(q);
    char* cptr=reinterpret_cast<char*>(const_cast<T**>(q));
    unsigned int* sz=reinterpret_cast<unsigned int*>(cptr-ArrayShift)-n;
    T* dp=NULL;
    imprint(dp,*q);
    char* cp=new char[ArrayShift+n*sizeof(unsigned int)+n*sizeof(T*)];
    BLASCopy(reinterpret_cast<unsigned int*>(cp),sz,n);
    reinterpret_cast<unsigned int*>(cp)+=n;
    *reinterpret_cast<unsigned int*>(cp+ArraySizeShift)=n;
    *reinterpret_cast<unsigned int*>(cp)=0;
    p=reinterpret_cast<T**>(cp+ArrayShift);
    p[0]=dp;
    for(unsigned int i=0;i<n-1;++i) p[i+1]=p[i]+sz[i];
  }

  template <typename T1,typename T2>
  void imprintStructure(T1**& p, const T2** q) {
    unsigned int n=size(q);
    char* cptr=reinterpret_cast<char*>(const_cast<T2**>(q));
    unsigned int* sz=reinterpret_cast<unsigned int*>(cptr-ArrayShift)-n;
    T1* dp=NULL;
    imprintStructure(dp,*q);
    char* cp=new char[ArrayShift+n*sizeof(unsigned int)+n*sizeof(T1*)];
    BLASCopy(reinterpret_cast<unsigned int*>(cp),sz,n);
    reinterpret_cast<unsigned int*>(cp)+=n;
    *reinterpret_cast<unsigned int*>(cp+ArraySizeShift)=n;
    *reinterpret_cast<unsigned int*>(cp)=0;
    p=reinterpret_cast<T1**>(cp+ArrayShift);
    p[0]=dp;
    for(unsigned int i=0;i<n-1;++i) p[i+1]=p[i]+sz[i];
  }

}

#endif

