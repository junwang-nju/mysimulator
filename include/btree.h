
#ifndef _Binary_Tree_H_
#define _Binary_Tree_H_

#include "btree-node.h"

namespace std {

  template <typename KeyType, typename ValueType>
  struct BTree {

    typedef BTreeNode<KeyType,ValueType>  NodeType;
    typedef BTree<KeyType,ValueType>      Type;

    NodeType *root;
    unsigned int state;

    BTree() : root(NULL) {}
    BTree(const Type&) { myError("Cannot create from BinaryTree"); }
    Type& operator=(const Type& BT) { assign(*this,BT); return *this; }
    ~BTree() { release(*this); }

  };

  template <typename KeyType, typename ValueType>
  void release(BTree<KeyType,ValueType>& BT) {
  }

  template <typename KeyType, typename ValueType>
  void assign(BTree<KeyType,ValueType>& destBT,
              const BTree<KeyType,ValueType>& srcBT) {
  }

  template <typename KeyType, typename ValueType>
  void refer(BTree<KeyType,ValueType>& destBT,
             const BTree<KeyType,ValueType>& srcBT) {
  }

  template <typename KeyType, typename ValueType>
  void insert(BTree<KeyType,ValueType>& destBT,
              const KeyType& key, const ValueType& value) {
  }

  template <typename KeyType, typename ValueType>
  void insert(BTree<KeyType,ValueType>& destBT,
              const BTreeNode<KeyType,ValueType>& srcBN) {
  }

  template <typename KeyType, typename ValueType>
  const ValueType* get(const BTree<KeyType,ValueType>& BT, const KeyType& key){
    return NULL;
  }

  template <typename KeyType, typename ValueType>
  const BTreeNode<KeyType,ValueType>* getNode(
      const BTree<KeyType,ValueType>& BT, const KeyType& key) {
    return NULL;
  }

  template <typename KeyType, typename ValueType>
  void removeNode(BTreeNode<KeyType,ValueType>& BN) {
  }

}

#endif

