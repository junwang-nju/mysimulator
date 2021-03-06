
#ifndef _List_Allocate_H_
#define _List_Allocate_H_

#include "list/interface.h"
#include "vector/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(List<T>& L, const unsigned int* lsize, const unsigned int nl) {
    assert(IsValid(lsize)&&(nl>0));
    release(L);
    unsigned int ne=0;
    unsigned int *p=const_cast<unsigned int*>(lsize);
    unsigned int *pend=p+nl;
    for(;p!=pend;)  ne+=(*(p++));
    allocate(static_cast<Vector<T>&>(L),ne);
    allocate(L.infra,nl);
    T *tp=L.pdata;
    for(unsigned int i=0;i<nl;tp+=lsize[i],++i)
      L.infra[i].getSubvec(tp,lsize[i]);
  }
  template <typename T>
  void allocate(List<T>& L, const Vector<unsigned int>& size) {
    allocate(L,size.pdata,size.size);
  }
  template <typename T>
  void imprint(List<T>& L, const List<T>& cL) {
    assert(IsValid(cL));
    Vector<unsigned int> sz(cL.ListSize());
    for(unsigned int i=0;i<sz.size;++i) sz[i]=cL.infra[i].size;
    allocate(L,sz);
    for(unsigned int i=0;i<sz.size;++i)
    for(unsigned int j=0;j<sz[i];j++) imprint(L[i][j],cL[i][j]);
  }

}

#endif

