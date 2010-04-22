
#ifndef _Binary_Tree_Node_H_
#define _Binary_Tree_Node_H_

#include "vector-impl.h"
#include "storage-state-name.h"
#include "error-proc.h"
#include "memory.h"
#include <cstdlib>
#include <cassert>

namespace std {

  enum BranchName {
    Unassigned=0,
    LeftBranch,
    RightBranch
  };

  template <typename KeyType, typename ValueType>
  struct BTreeNode {

    typedef BTreeNode<KeyType,ValueType>  Type;

    KeyType* key;
    ValueType* value;
    Type* parent;
    Type* left;
    Type* right;
    unsigned int branch;
    unsigned int keystate;
    unsigned int valuestate;

    BTreeNode()
      : key(NULL), value(NULL), parent(NULL), left(NULL), right(NULL),
        branch(Unassigned), keystate(Unused), valuestate(Unused) {}
    BTreeNode(const Type&) { myError("Cannot create from BinaryTree Node"); }
    Type& operator=(const Type& BN) { assign(*this,BN); return *this; }
    ~BTreeNode() { release(*this); }

  };

  template <typename KeyType, typename ValueType>
  bool IsAvailable(const BTreeNode<KeyType,ValueType>& BN) {
    return IsAvailable(BN.key)&&IsAvailable(BN.value);
  }

  template <typename KeyType, typename ValueType>
  void assign(BTreeNode<KeyType,ValueType>& destBN,
              const BTreeNode<KeyType,ValueType>& srcBN) {
    assert(IsAvailable(srcBN));
    release(destBN);
    destBN.key=srcBN.key;
    destBN.value=srcBN.value;
    destBN.keystate=Reference;
    destBN.valuestate=Reference;
  }

  template <typename KeyType, typename ValueType>
  void release(BTreeNode<KeyType,ValueType>& BN) {
    if(BN.keystate==Allocated)      safe_delete(BN.key);    else BN.key=NULL;
    if(BN.valuestate==Allocated)    safe_delete(BN.value);  else BN.value=NULL;
    BN.parent=NULL;
    safe_delete(BN.left);
    safe_delete(BN.right);
    BN.branch=Unassigned;
    BN.keystate=Unused;
    BN.valuestate=Unused;
  }

}

#endif

