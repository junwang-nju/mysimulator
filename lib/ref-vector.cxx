
#include "ref-vector.h"

namespace std {

  template <typename T>
  void refVector<T>::refer(refVector<T>& V) { refer(V,0,V.size()); }

  template <typename T>
  void refVector<T>::refer(ObjectWStorage<VectorBase<T> >& V) {
    refer(V,0,V.size());
  }

  template <typename T>
  void refVector<T>::refer(refVector<T>& V, const unsigned int off,
                           const unsigned int sz) {
    assert(off+sz<=V.size());
    if(this->IsAvailable()) this->RefInfo().remove_self();
    this->data()=const_cast<T*>(V.data())+off;
    this->SetSize(sz);
    this->SetHeadTail();
    V.RefInfo().add_before(this->RefInfo());
  }

  template <typename T>
  void refVector<T>::refer(ObjectWStorage<VectorBase<T> >& V,
                           const unsigned int off, const unsigned int sz) {
    assert(off+sz<=V.size());
    if(this->IsAvailable()) this->RefInfo().remove_self();
    this->data()=const_cast<T*>(V.data())+off;
    this->SetSize(sz);
    this->SetHeadTail();
    V.RefList().append(this->RefInfo());
  }

  template <typename T>
  const char* refVector<T>::type() const { return "Reference Vector"; }

}

