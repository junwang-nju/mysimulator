
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

    BTree() : root(NULL), state(Unused) {}
    BTree(const Type&) { myError("Cannot create from BinaryTree"); }
    Type& operator=(const Type& BT) { assign(*this,BT); return *this; }
    ~BTree() { release(*this); }

  };

  template <typename KeyType, typename ValueType>
  void release(BTree<KeyType,ValueType>& BT) {
    if(BT.state=Allocated) {
      BTreeNode<KeyType,ValueType> *present, *tofree;
      present=BT.root;
      while(IsAvailable(present)) {
        if(IsAvailable(present->left))  present=present->left;
        else if(IsAvailable(present->right))  present=present->right;
        else {
          tofree=present;
          present=tofree->parent;
          if(tofree->branch==LeftBranch) present->left=NULL;
          else if(tofree->branch==RightBranch)  present->right=NULL;
          safe_delete(tofree);
        }
      }
    } else BT.root=NULL;
    BT.state=Unused;
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
  void removeNode(BTree<KeyType,ValueType>& BT,
                  const BTreeNode<KeyType,ValueType>* BN){
    assert(BN==getNode(BT,*(BN->key)));
    if(IsAvailable(BN)) {
      if(!IsAvailable(BN->left)) {
        if(IsAvailable(BN->parent)) {
          if(BN->branch==LeftBranch)  BN->parent->left=BN->right;
          else if(BN->branch==RightBranch)  BN->parent->right=BN->right;
          else myError("Improper Branch Flag");
        } else root=BN->right;
        BN->right=NULL;
      } else if(!IsAvailable(BN->right)) {
        if(IsAvailable(BN->parent)) {
          if(BN->branch==LeftBranch)  BN->parent->left=BN->left;
          else if(BN->branch==RightBranch)  BN->parent->right=BN->left;
          else myError("Improper Branch Flag");
        } else root=BN->left;
        BN->left=NULL;
      } else {
        BTreeNode<KeyType,ValueType> *movenode;
        movenode=BN->right;
        while(IsAvailable(movenode->left))  movenode=movenode.left;
        if(movenode->branch==LeftBranch)
          movenode->parent->left=movenode->right;
        else if(movenode->branch==RightBranch)
          movenode->parent->right=movenode->right;
        if(IsAvailable(movenode->right)) {
          movenode->right->parent=movenode->parent;
          movenode->right->branch=movenode->branch;
        }
        movenode->parent=BN->parent;
        movenode->branch=BN->branch;
        if(IsAvailable(movenode->parent)) {
          if(movenode->branch==LeftBranch)
            movenode->parent->left=movenode;
          else if(movenode->branch==RightBranch)
            movenode->parent->right=movenode;
          else myError("Improper Branch Flag");
        } else root=movenode;
        movenode->left=BN->left;  BN->left=NULL;
        movenode->right=BN->right;  BN->right=NULL;
      }
    }
  }

}

#endif

