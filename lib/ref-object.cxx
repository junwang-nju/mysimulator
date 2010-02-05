
#include "ref-object.h"

namespace std {

  template <typename RObjType, typename SObjType>
  ChainNode<void*>& refObject<RObjType,SObjType>::RefInfo() { return rNode; }

  template <typename RObjType, typename SObjType>
  const ChainNode<void*>& refObject<RObjType,SObjType>::RefInfo() const {
    return rNode;
  }

  template <typename RObjType, typename SObjType>
  void refObject<RObjType,SObjType>::clear() {
    static_cast<ParentType*>(this)->clear();
    rNode.remove_self();
  }

}

