
#include "pool.h"
#include "memory.h"
#include <cassert>

namespace std {

  template <typename T>
  T& Pool<T>::operator[](const unsigned int& I) {
    assert(I<nUsed);
    return static_cast<ParentType*>(this)->operator[](I);
  }

  template <typename T>
  const T& Pool<T>::operator[](const unsigned int& I) const {
    assert(I<nUsed);
    return static_cast<const ParentType*>(this)->operator[](I);
  }

  template <typename T>
  const unsigned int& Pool<T>::capacity() const {
    return static_cast<const ParentType*>(this)->size();
  }

  template <typename T>
  void Pool<T>::allocate(const unsigned int& Max) {
    static_cast<ParentType*>(this)->data()=new T[Max];
    nUsed=0;
  }

  template <typename T>
  void Pool<T>::clear() {
    nUsed=0;
    safe_delete(static_cast<ParentType*>(this)->data());
    static_cast<ParentType*>(this)->clear();
  }

  template <typename T>
  void Pool<T>::add(const T& mer) {
    if(nUsed==capacity()) myError("Pool is Full");
    static_cast<ParentType*>(this)->operator[](nUsed)=mer;
    ++nUsed;
  }

  template <typename T>
  void Pool<T>::del(const unsigned int& I) {
    assert(I<nUsed);
    if(I<nUsed-1)
      static_cast<ParentType*>(this)->operator[](I)=
          static_cast<ParentType*>(this)->operator[](nUsed-1);
    --nUsed;
  }

  template <typename T>
  void Pool<T>::swap(Pool<T>& P) {
    unsigned int tmn;
    tmn=nUsed;  nUsed=P.nUsed;  P.nUsed=tmn;
    static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(P));
  }

  template <typename T>
  const char* Pool<T>::type() { return "Pool"; }

}

