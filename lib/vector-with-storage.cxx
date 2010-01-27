
#include "vector-with-storage.h"

namespace std {

  template <typename T>
  void VectorWStorage<T>::clear() {
    rObjSet.clear();
    static_cast<ParentType*>(this)->clear();
  }

  template <typename T>
  Pool<void*>& VectorWStorage<T>::RefList() { return rObjSet; }

  template <typename T>
  const Pool<void*>& VectorWStorage<T>::RefList() const { return rObjSet; }

  template <typename T>
  void VectorWStorage<T>::swap(VectorWStorage<T>& RV) {
    static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(RV));
    rObjSet.swap(RV.rObjSet);
  }

}

