
#ifndef _Property_List_H_
#define _Property_List_H_

#include "vector.h"
#include <cassert>

namespace std {

  template <typename T>
  struct PropertyList {
    T* data;
    Vector<T>* structure;
    unsigned int size;
    unsigned int dsize;
    unsigned int state;

    typedef PropertyList<T> Type;

    PropertyList()
      : data(NULL), structure(NULL), size(0), dsize(0), state(Unused) {}
    PropertyList(const Type&) { myError("Cannor create from PropertyList"); }
    Type& operator=(const Type& PL) { assign(*this,PL); return *this; }
    ~PropertyList() { release(*this); }

    Vector<T>& operator[](const unsigned int I) { return structure[I]; }
    const Vector<T>& operator[](const unsigned int I) const {
      return structure[I];
    }

  };

  template <typename T>
  bool IsAvailable(const PropertyList<T>& PL) { return IsAvailable(PL.data); }

  template <typename T>
  void release(PropertyList<T>& PL) {
    if(PL.state==Allocated) {
      safe_delete_array(PL.data);
      for(unsigned int i=0;i<PL.size;++i) release(PL.structure[i]);
      safe_delete_array(PL.structure);
    } else {
      PL.data=NULL;
      PL.structure=NULL;
    }
    PL.size=0;
    PL.dsize=0;
    PL.state=Unused;
  }

  template <typename T>
  void assign(PropertyList<T>& destPL, const PropertyList<T>& srcPL) {
    assert(IsAvailable(destPL));
    assert(IsAvailable(srcPL));
    unsigned int n=(destPL.size<srcPL.size?destPL.size:srcPL.size);
    for(unsigned int i=0;i<n;++i)
      assign(destPL.structure[i],srcPL.structure[i]);
  }

  template <typename T>
  void allocate(PropertyList<T>& PL,
                const unsigned int *vsize, const unsigned int size) {
    release(PL);
    PL.state=Allocated;
    PL.size=size;
    PL.dsize=0;
    for(unsigned int i=0;i<size;++i)  PL.dsize+=vsize[i];
    PL.data=new T[PL.dsize];
    PL.structure=new Vector<T>[size];
    T* dPtr=PL.data;
    for(unsigned int i=0;i<size;++i,dPtr+=vsize[i]) refer(PL[i],dPtr,vsize[i]);
  }

  template <typename T>
  void refer(PropertyList<T>& destPL, const PropertyList<T>& srcPL) {
    assert(IsAvailable(srcPL));
    release(destPL);
    destPL.data=srcPL.data;
    destPL.structure=srcPL.structure;
    destPL.size=srcPL.size;
    destPL.dsize=srcPL.dsize;
    destPL.state=Reference;
  }

  template <typename T>
  void swap(PropertyList<T>& PLA, PropertyList<T>& PLB) {
    swap(PLA.data,PLB.data);
    swap(PLA.structure,PLB.structure);
    swap(PLA.size,PLB.size);
    swap(PLA.dsize,PLB.dsize);
    swap(PLA.state,PLB.state);
  }

  template <typename T>
  ostream& operator<<(ostream& os, const PropertyList<T>& PL) {
    assert(IsAvailable(PL));
    os<<PL[0];
    for(unsigned int k=1;k<PL.size;++k) os<<endl<<PL[k];
    return os;
  }

}

#endif

