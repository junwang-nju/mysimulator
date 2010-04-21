
#ifndef _Bianry_Tree_Node_H_
#define _Bianry_Tree_Node_H_

#include "storage-state-name.h"
#include "error-proc.h"
#include <cstdlib>

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
    unsigned int parentstate;
    unsigned int leftstate;
    unsigned int rightstate;

    BTreeNode()
      : key(NULL), value(NULL), parent(NULL), left(NULL), right(NULL),
        branch(Unassigned), keystate(Unused), valuestate(Unused),
        parentstate(Unused), leftstate(Unused), rightstate(Unused) {}
    BTreeNode(const Type&) { myError("Cannot create from BinaryTree Node"); }
    Type& operator=(const Type& BN) { assign(*this,BN); return *this; }
    ~BTreeNode() { release(*this); }

  };

  template <typename KeyType, typename ValueType>
  void assign(BTreeNode<KeyType,ValueType>& destBN,
              const BTreeNode<KeyType,ValueType>& srcBN) {
    release(destBN);
    destBN.key=srcBN.key;
    destBN.value=srcBN.value;
    destBN.keystate=Reference;
    destBN.valuestate=Reference;
  }

  template <typename KeyType, typename ValueType>
  void release(BTreeNode<KeyType,ValueType>& BN) {
    if(BN.keystate==Allocated)      release(BN.key);    else BN.key=NULL;
    if(BN.valuestate==Allocated)    release(BN.value);  else BN.value=NULL;
    if(BN.parentstate==Allocated)   release(BN.parent); else BN.parent=NULL;
    if(BN.leftstate==Allocated)     release(BN.left);   else BN.left=NULL;
    if(BN.rightstate==Allocated)    release(BN.right);  else BN.right=NULL;
    BN.branch=Unassigned;
    BN.keystate=Unused;
    BN.valuestate=Unused;
    BN.parentstate=Unused;
    BN.leftstate=Unused;
    BN.rightstate=Unused;
  }

}

#endif

