
#ifndef _Binary_Tree_Node_Copy_H_
#define _Binary_Tree_Node_Copy_H_

#include "btree/node/interface.h"
#include "referable-object/copy.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  void copy(BTreeNode<KeyType,ValueType>& N,
            const BTreeNode<KeyType,ValueType>& cN) {
    assert(IsValid(N)&&IsValid(cN));
    copy(N.key,cN.key);
    copy(N.value,cN.value);
  }

}

#endif

