
#ifndef _Property_List_H_
#define _Property_List_H_

#include "vector.h"
#include <cassert>

namespace std {

  template <typename T>
  struct PropertyList : public Vector<T> {

    Vector<T>* structure;
    unsigned int nunit;

    typedef PropertyList<T> Type;
    typedef Vector<T>   ParentType;

    PropertyList() : ParentType(), structure(NULL), nunit(0) {}
    PropertyList(const Type&) { myError("Cannor create from PropertyList"); }
    Type& operator=(const Type& PL) { assign(*this,PL); return *this; }
    ~PropertyList() { release(*this); }

    Vector<T>& operator[](const unsigned int I) { return structure[I]; }
    const Vector<T>& operator[](const unsigned int I) const {
      return structure[I];
    }

  };

  template <typename T>
  bool IsAvailable(const PropertyList<T>& PL) {
    return IsAvailable(static_cast<const Vector<T>&>(PL));
  }

  template <typename T>
  void release(PropertyList<T>& PL) {
    if(PL.state==Allocated) {
      //for(unsigned int i=0;i<PL.size;++i) release(PL.structure[i]);
      safe_delete_array(PL.structure);
    } else  PL.structure=NULL;
    PL.nunit=0;
    release(static_cast<Vector<T>&>(PL));
  }

  template <typename T>
  void assign(PropertyList<T>& destPL, const PropertyList<T>& srcPL) {
    assert(IsAvailable(destPL));
    assert(IsAvailable(srcPL));
    unsigned int n=(destPL.nunit<srcPL.nunit?destPL.nunit:srcPL.nunit);
    for(unsigned int i=0;i<n;++i)
      assign(destPL.structure[i],srcPL.structure[i]);
  }

  template <typename T>
  void allocate(PropertyList<T>& PL, const unsigned int size) {
    myError("allocate for vector is prohibited for proerpty list");
  }

  template <typename T>
  void allocate(PropertyList<T>& PL,
                const unsigned int *vsize, const unsigned int size) {
    release(PL);
    PL.nunit=size;
    unsigned int dsize=0;;
    for(unsigned int i=0;i<size;++i)  dsize+=vsize[i];
    allocate(static_cast<Vector<T>&>(PL),dsize);
    PL.structure=new Vector<T>[size];
    T* dPtr=PL.data;
    for(unsigned int i=0;i<size;++i,dPtr+=vsize[i]) refer(PL[i],dPtr,vsize[i]);
  }

  template <typename T>
  void refer(PropertyList<T>& destPL, const PropertyList<T>& srcPL) {
    assert(IsAvailable(srcPL));
    release(destPL);
    destPL.structure=srcPL.structure;
    destPL.nunit=srcPL.nunit;
    refer(static_cast<Vector<T>&>(destPL),static_cast<const Vector<T>&>(srcPL));
  }

  template <typename T>
  void swap(PropertyList<T>& PLA, PropertyList<T>& PLB) {
    swap(PLA.structure,PLB.structure);
    swap(PLA.nunit,PLB.nunit);
    swap(static_cast<Vector<T>&>(PLA),static_cast<Vector<T>&>(PLB));
  }

  template <typename T>
  ostream& operator<<(ostream& os, const PropertyList<T>& PL) {
    assert(IsAvailable(PL));
    os<<PL[0];
    for(unsigned int k=1;k<PL.nunit;++k) os<<endl<<PL[k];
    return os;
  }

}

#endif

