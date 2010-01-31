
#ifndef _Binary_Tree_H_
#define _Binary_Tree_H_

#include "btree-node.h"

namespace std {
  template <typename KeyType, typename ValueType>
  class BTree {
    public:
      typedef BTree<KeyType,ValueType>  Type;
      typedef BTreeNode<KeyType,ValueType>  NodeType;
    protected:
      NodeType Root;
    public:
      BTree() : Root() {}
      BTree(const Type& bt) { myError("Cannot create from binary tree"); }
      ~BTree() { clear(); }
      void clear();
      void insert(const KeyType& K, const ValueType& V);
      const ValueType* get(const KeyType& K) const;
      void remove(NodeType*& nd);
  };
}

#endif

