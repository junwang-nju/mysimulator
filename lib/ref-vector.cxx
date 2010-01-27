
#include "ref-vector.h"

namespace std {

  template <typename T>
  void refVector<T>::refer(const refVector<T>& V) { refer(V,0,V.size()); }

  template <typename T>
  void refVector<T>::refer(const ObjectWStorage<VectorBase<T> >& V) {
    refer(V,0,V.size());
  }

  template <typename T>
  void refVector<T>::refer(const refVector<T>& V, const unsigned int off,
                           const unsigned int sz) {
    assert(off+sz<=V.size());
    if(this->IsAvailable()) {
      this->PtrRefList()->del(this->PresentID());
      this->PtrRefList()=NULL;
      this->SetID(-1);
    }
    this->data()=const_cast<T*>(V.data())+off;
    this->SetSize(sz);
    this->SetHeadTail();
    this->PtrRefList()=const_cast<Pool<void*>*>(V.PtrRefList());
    this->PtrRefList()->add(static_cast<void*>(this));
    this->SetID(this->PtrRefList()->used()-1);
  }

  template <typename T>
  void refVector<T>::refer(const ObjectWStorage<VectorBase<T> >& V,
                           const unsigned int off, const unsigned int sz) {
    assert(V.RefList().used()<V.RefList().capacity());
    assert(off+sz<=V.size());
    if(this->IsAvailable()) {
      this->PtrRefList()->del(this->PresentID());
      this->PtrRefList()=NULL;
      this->SetID(-1);
    }
    this->data()=const_cast<T*>(V.data())+off;
    this->SetSize(sz);
    this->SetHeadTail();
    this->PtrRefList()=const_cast<Pool<void*>*>(&(V.RefList()));
    this->PtrRefList()->add(static_cast<void*>(this));
    this->SetID(this->PtrRefList()->used()-1);
  }

  template <typename T>
  const char* refVector<T>::type() const { return "Reference Vector"; }

}

