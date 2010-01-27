
#include "object-with-storage.h"

namespace std {

  template <typename ObjType>
  void ObjectWStorage<ObjType>::clear() {
    rObjSet.clear();
    static_cast<ParentType*>(this)->clear();
  }

  template <typename ObjType>
  Pool<void*>& ObjectWStorage<ObjType>::RefList() { return rObjSet; }

  template <typename ObjType>
  const Pool<void*>& ObjectWStorage<ObjType>::RefList() const {
    return rObjSet;
  }

  template <typename ObjType>
  void ObjectWStorage<ObjType>::swap(ObjectWStorage<ObjType>& O) {
    static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(O));
    rObjSet.swap(O.rObjSet);
  }

}

