
#include "referable-vector.h"

namespace std {

  template <typename T>
  void referableVector<T>::clear() {
    rObjSet.clear();
    static_cast<ParentType*>(this)->clear();
  }

  template <typename T>
  Pool<void*>& referableVector<T>::RefList() { return rObjSet; }

  template <typename T>
  const Pool<void*>& referableVector<T>::RefList() const { return rObjSet; }

  template <typename T>
  void referableVector<T>::swap(referableVector<T>& RV) {
    static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(RV));
    rObjSet.swap(RV.rObjSet);
  }

}

