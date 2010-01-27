
#include "ref-object.h"

namespace std {

  template <typename ObjType>
  Pool<void*>* refObject<ObjType>::PtrRefList() { return pRefList; }

  template <typename ObjType>
  const Pool<void*>* refObject<ObjType>::PtrRefList() const{ return pRefList; }

  template <typename ObjType>
  const int& refObject<ObjType>::PresentID() const { return thisID; }

  template <typename ObjType>
  void refObject<ObjType>::SetID(const int id) { thisID=id; }

  template <typename ObjType>
  void refObject<ObjType>::clear() {
    static_cast<ParentType*>(this)->clear();
    pRefList=NULL;
    thisID=-1;
  }

  template <typename ObjType>
  void refObject<ObjType>::swap(refObject<ObjType>& O) {
    static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(O));
    Pool<void*>* tpPtr;
    tpPtr=pRefList; pRefList=O.pRefList;  O.pRefList=tpPtr;
    int n;
    n=thisID; thisID=O.thisID;  O.thisID=n;
  }

}

