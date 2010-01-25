
#include "ref-vector.h"

namespace std {

  template <typename T>
  void refVector<T>::clear() {
    static_cast<ParentType*>(this)->clear();
    pRefList=NULL;
    thisID=-1;
  }

  template <typename T>
  void refVector<T>::refer(const referableVector<T>& V) {
    refer(V,uZero,V.size());
  }

  template <typename T>
  void refVector<T>::refer(const referableVector<T>& V,
                           const unsigned int& off, const unsigned int& sz) {
    assert(V.RefList().used()<V.RefList().capacity());
    assert(off+sz<=V.size());
    if(this->IsAvailable()) {
      pRefList->del(thisID);
      pRefList=NULL;
      thisID=-1;
    }
    this->data()=const_cast<T*>(V.data())+off;
    this->SetSize(sz);
    this->SetHeadTail();
    pRefList=const_cast<Pool<void*>*>(&(V.RefList()));
    pRefList->add(static_cast<void*>(this));
    thisID=pRefList->used()-1;
  }

  template <typename T>
  void refVector<T>::swap(refVector<T>& V) {
    static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(V));
    Pool<void*>* tPPtr;
    tPPtr=pRefList; pRefList=V.pRefList;  V.pRefList=tPPtr;
    int n;
    n=thisID; thisID=V.thisID;  V.thisID=n;
  }

  template <typename T>
  const char* refVector<T>::type() const { return "Reference Vector"; }

}

