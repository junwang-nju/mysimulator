
#ifndef _Binary_Tree_Node_Allocate_H_
#define _Binary_Tree_Node_Allocate_H_

#include "btree/node/interface.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  void allocate(BTreeNode<KeyType,ValueType>& N) {
    release(N);
    allocate(N.key);
    allocate(N.value);
  }

  template <typename KeyType, typename ValueType>
  void imprint(BTreeNode<KeyType,ValueType>& N,
               const BTreeNode<KeyType,ValueType>&) {
    allocate(N);
  }

}

#endif

