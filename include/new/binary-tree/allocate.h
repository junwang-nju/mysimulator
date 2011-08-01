
#ifndef _Binary_Tree_Allocate_H_
#define _Binary_Tree_Allocate_H_

#include "binary-tree/interface.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  void allocate(BTree<KeyType,ValueType>& B) { release(B); }

}

#endif

