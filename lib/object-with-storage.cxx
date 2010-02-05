
#include "object-with-storage.h"

namespace std {

  template <typename ObjType>
  void ObjectWStorage<ObjType>::clear() {
    rObjSet.clear();
    static_cast<ParentType*>(this)->clear();
  }

  template <typename ObjType>
  Chain<void*>& ObjectWStorage<ObjType>::RefList() { return rObjSet; }

  template <typename ObjType>
  const Chain<void*>& ObjectWStorage<ObjType>::RefList() const {
    return rObjSet;
  }

}

