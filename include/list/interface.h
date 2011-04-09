
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

}

#endif

