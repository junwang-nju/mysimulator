
#ifndef _Property_List_H_
#define _Property_List_H_

#include "vector.h"

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
    Type& operator=(const Type& PL) {
      IsAvailable(*this);
      IsAvailable(PL);
      unsigned int n=(size<PL.size?size:PL.size);
      for(unsigned int i=0;i<n;++i) assign(structure[i],PL.structure[i]);
      return *this;
    }
    ~PropertyList() { release(*this); }

  };

  template <typename T>
  bool IsAvailable(const PropertyList<T>& PL) { return IsAvailable(PL.data); }

  template <typename T>
  void release(PropertyList<T>& PL) {
    if(PL.state==Allocated) {
      safe_delete_array(PL.data);
      safe_delete_array(PL.structure);
    } else {
      PL.data=NULL;
      PL.structure=NULL;
    }
    PL.size=0;
    PL.dsize=0;
    PL.state=Unused;
  }

}

#endif

