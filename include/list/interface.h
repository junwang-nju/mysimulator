
#ifndef _List_Interface_H_
#define _List_Interface_H_

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  struct List : public Vector<T> {

    typedef List<T>   Type;
    typedef Vector<T> ParentType;

    Vector<Vector<T> >  infra;

    List() : ParentType(), infra() {}
    List(const Type&) { Error("Copier of List Disabled!"); }
    Type& operator(const Type&) {
      Error("Operator= for List Disabled!");
      return *this;
    }
    ~List() { clearData(); }

    void clearData() {
      release(infra);
      release(static_cast<ParentType&>(*this));
    }
    Vector<T>& operator[](const unsigned int I) { return infra[I]; }
    const Vector<T>& operator[](const unsigned int I) const { return infra[I]; }
    const unsigned int ListSize() const { return infra.size; }
    const unsigned int NumElements() const { return size; }

  };

  template <typename T>
  bool IsValid(const List<T>& L) {
    return IsValid(static_cast<const Vector<T>&>(L))&&IsValid(L.infra);
  }
  template <typename T>
  void release(List<T>& L) { L.clearData(); }

  template <typename T>
  void allocate(List<T>& L, const unsigned int* lsize, const unsigned int nl) {
    assert(IsValid(lsize));
    release(L);
    unsigned int ne=0;
    unsigned int *p=const_cast<unsigned int*>(lsize);
    unsigned int *pend=p+nl;
    for(;p!=pend;)  ne+=(*(p++));
    allocate(static_cast<Vector<T>&>(L),ne);
    allocate(L.infra,nl);
    p=L.data;
    for(unsigned int i=0;i<nl;p+=lsize[i],++i) L.infra[i].getSubvec(p,lsize[i]);
  }

}

#endif

