
#include "ref-object.h"

namespace std {

  template <typename RObjType, typename SObjType>
  ChainNode<void*> refObject<RObjType,SObjType>::RefInfo() { return rNode; }

  template <typename RObjType, typename SObjType>
  const ChainNode<void*> refObject<RObjType,SObjType>::RefInfo() const {
    return rNode;
  }

  template <typename RObjType, typename SObjType>
  void refObject<RObjType,SObjType>::clear() {
    static_cast<ParentType*>(this)->clear();
    rNode.remove_self();
  }

  template <typename RObjType, typename SObjType>
  void refObject<RObjType,SObjType>::swap(refObject<RObjType,SObjType>& O) {
    static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(O));
    ChainNode<void*>* pNode;
    pNode=rNode.parent();
    rNode.parent()=O.rNode.parent();
    O.rNode.parent()=pNode;
    pNode=rNode.child();
    rNode.child()=O.rNode.child();
    O.rNode.child()=pNode;
  }

}

