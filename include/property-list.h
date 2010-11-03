
#ifndef _Property_List_H_
#define _Property_List_H_

#include "vector.h"

namespace std {

  template <typename T>
  struct PropertyList : public Vector<T> {
    typedef PropertyList<T>   Type;
    typedef Vector<T> ParentType;
    Vector<T>* structure;
    unsigned int nunit;
    
    PropertyList() : ParentType(), structure(), nunit(0) {}
    PropertyList(const Type& L) { myError("Cannot create from PropertyList"); }
    Type& operator=(const Type& L) {
      MyError("Cannot copy PropertyList");
      return *this;
    }
    ~PropertyList() { release(*this); }
  };

  template <typename T>
  bool IsAvailable(const PropertyList<T>& L) {
    return IsAvailable(static_cast<const Vector<T>&>(L));
  }

  template <typename T>
  void release(PropertyList<T>& L) {
    if(L.state==Allocated) safe_delete_array(L.structure);
    else L.structure=NULL;
    L.nunit=0;
    release(static_cast<Vector<T>&>(L));
  }

  template <typename T>
  void copy(PropertyList<T>& L, const PropertyList<T>& sL) {
    assert(IsAvailable(L));
    assert(IsAvailable(sL));
    unsigned int n=(L.nunit<sL.nunit?L.nunit:sL.nunit);
    for(unsigned int i=0;i<n;++i) copy(L.structure[i],sL.structure[i]);
  }

  template <typename T>
  void allocate(PropertyList<T>& L,
                const unsigned int* vsize, const unsigned int size) {
    release(L);
    L.nunit=size;
    unsigned int dsize=0;
    for(unsigned int i=0;i<size;++i)  dsize+=vsize[i];
    allocate(static_cast<Vector<T>&>(L),dsize);
    L.structure=new Vector<T>[size];
    T* dPtr=L.data;
    for(unsigned int i=0;i<size;dPtr+=vsize[i],++i)  refer(L[i],dPtr,vsize[i]);
  }

}

#endif
