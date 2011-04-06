
#ifndef _Binary_Tree_Node_Interface_H_
#define _Binary_Tree_Node_Interface_H_

#include "referable-object/interface.h"
#include "btree/branch-name.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  struct BTreeNode {

    typedef BTreeNode<KeyType,ValueType>  Type;

    Object<KeyType> key;
    Object<ValueType> value;
    BranchName workBranch;
    Type* left;
    Type* right;
    Type* parent;

    BTreeNode() : key(), value(), workBranch(Unassigned), left(NULL),
                  right(NULL), parent(NULL) {}
    BTreeNode(const Type&) { Error("Copier of BTreeNode Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for BTreeNode Disabled!");
      return *this;
    }
    ~BTreeNode() { clearData(); }

    void clearData() {
      release(key);
      release(value);
      workBranch=Unassigned;
      release(left);
      release(right);
      parent=NULL;
    }

  };

  template <typename KeyType, typename ValueType>
  bool IsValid(const BTreeNode<KeyType,ValueType>& N) {
    return IsValid(N.key)&&IsValid(N.value);
  }
  template <typename KeyType, typename ValueType>
  void release(BTreeNode<KeyType,ValueType>& N) { N.clearData(); }

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

