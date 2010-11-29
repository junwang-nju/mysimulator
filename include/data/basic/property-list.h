
#ifndef _Property_List_H_
#define _Property_List_H_

#include "operation/basic/vector-op.h"

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
      myError("Cannot copy PropertyList");
      return *this;
    }
    ~PropertyList() { release(*this); }
    Vector<T>& operator[](const unsigned int I) { return structure[I]; }
    const Vector<T>& operator[](const unsigned int I) const {
      return structure[I];
    }
  };

  template <typename T>
  bool IsAvailable(const PropertyList<T>& L) {
    return IsAvailable(static_cast<const Vector<T>&>(L));
  }

  template <typename T>
  bool IsStructureSame(const PropertyList<T>& LA, const PropertyList<T>& LB) {
    assert(IsAvailable(LA));
    assert(IsAvailable(LB));
    unsigned int n=LA.nunit;
    if(n!=LB.nunit) return false;
    for(unsigned int i=0;i<n;++i)
      if(LA.structure[i].size!=LB.structure[i].size)  return false;
    return true;
  }

  template <typename T>
  void release(PropertyList<T>& L) {
    if(L.state==Allocated) safe_delete_array(L.structure);
    else L.structure=NULL;
    L.nunit=0;
    release(static_cast<Vector<T>&>(L));
  }

  template <typename T, typename cT>
  void copy(PropertyList<T>& L, const PropertyList<cT>& sL) {
    assert(IsAvailable(L));
    assert(IsAvailable(sL));
    unsigned int n=(L.nunit<sL.nunit?L.nunit:sL.nunit);
    for(unsigned int i=0;i<n;++i) copy<T,cT>(L.structure[i],sL.structure[i]);
  }

  template <typename T>
  void ecopy(PropertyList<T>& L, const PropertyList<T>& cL) {
    assert(IsStructureSame(L,cL));
    copy(static_cast<Vector<T>&>(L),static_cast<const Vector<T>&>(cL));
  }

  template <typename T>
  void allocate(PropertyList<T>& L,
                const unsigned int* vsize, const unsigned int size) {
    assert(IsAvailable(vsize));
    release(L);
    L.nunit=size;
    unsigned int dsize=0;
    for(unsigned int i=0;i<size;++i)  dsize+=vsize[i];
    allocate(static_cast<Vector<T>&>(L),dsize);
    L.structure=new Vector<T>[size];
    T* dPtr=L.data;
    for(unsigned int i=0;i<size;dPtr+=vsize[i],++i)  refer(L[i],dPtr,vsize[i]);
  }

  template <typename T>
  void allocate(PropertyList<T>& L,
                const Vector<unsigned int>& vsize) {
    allocate(L,vsize.data,vsize.size);
  }

  template <typename T, typename aT>
  void imprint(PropertyList<T>& L, const PropertyList<aT>& aL) {
    assert(IsAvailable(aL));
    Vector<unsigned int> sz(aL.nunit);
    for(unsigned int i=0;i<aL.nunit;++i)  sz[i]=aL[i].size;
    allocate(L,sz);
  }

  template <typename T>
  void refer(PropertyList<T>& L, const PropertyList<T>& rL) {
    assert(IsAvailable(rL));
    release(L);
    L.structure=rL.structure;
    L.nunit=rL.nunit;
    refer(static_cast<Vector<T>&>(L),static_cast<const Vector<T>&>(rL));
  }

  template <typename T>
  void swap(PropertyList<T>& LA, PropertyList<T>& LB) {
    swap(LA.structure,LB.structure);
    swap(LA.nunit,LB.nunit);
    swap(static_cast<Vector<T>&>(LA),static_cast<Vector<T>&>(LB));
  }

  template <typename T>
  ostream& operator<<(ostream& os, const PropertyList<T>& L) {
    assert(IsAvailable(L));
    os<<L[0];
    for(unsigned int k=1;k<L.nunit;++k) os<<endl<<L[k];
    return os;
  }

}

#endif
