
#ifndef _Binary_Tree_H_
#define _Binary_Tree_H_

#include "btree-node.h"

namespace std {

  template <typename KeyType, typename ValueType>
  struct BTree {

    typedef BTreeNode<KeyType,ValueType>  NodeType;
    typedef BTree<KeyType,ValueType>      Type;

    NodeType *root;

    BTree() : root(NULL) {}
    BTree(const Type&) { myError("Cannot create from BinaryTree"); }
    Type& operator=(const Type& BT) { assign(*this,BT); return *this; }
    ~BTree() { release(*this); }

  };

  template <typename KeyType, typename ValueType>
  void release(BTree<KeyType,ValueType>& BT) {
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
        else if(tofree->branch==Unassigned) {}
        else myError("Unknown Branch Flag");
        safe_delete(tofree);
      }
    }
    BT.root=NULL;
  }

  template <typename KeyType, typename ValueType>
  void assign(BTreeNode<KeyType,ValueType>*& destBN,
              const BTreeNode<KeyType,ValueType>* srcBN,
              const BTreeNode<KeyType,ValueType>* destPN,
              const unsigned int destBR) {
    safe_delete(destBN);
    if(IsAvailable(srcBN)) {
      destBN=new BTreeNode<KeyType,ValueType>;
      destBN->key=new KeyType;
      destBN->value=new ValueType;
      *(destBN->key)=*(srcBN->key);
      *(destBN->value)=*(srcBN->value);
      destBN->keystate=Allocated;
      destBN->valuestate=Allocated;
      destBN->parent=const_cast<BTreeNode<KeyType,ValueType>*>(destPN);
      destBN->branch=destBR;
      if(IsAvailable(srcBN->left))
        assign(destBN->left,srcBN->left,destBN,LeftBranch);
      if(IsAvailable(srcBN->right))
        assign(destBN->right,srcBN->right,destBN,RightBranch);
    }
  }

  template <typename KeyType, typename ValueType>
  void assign(BTree<KeyType,ValueType>& destBT,
              const BTree<KeyType,ValueType>& srcBT) {
    release(destBT);
    assign(destBT.root,srcBT.root,
           static_cast<const BTreeNode<KeyType,ValueType>*>(NULL),
           Unassigned);
  }

  template <typename KeyType, typename ValueType>
  void insert(BTree<KeyType,ValueType>& destBT,
              const KeyType& key, const ValueType& value) {
    BTreeNode<KeyType,ValueType> *present;
    int cmp;
    present=destBT.root;
    while(IsAvailable(present)) {
      cmp=compare(key,*(present->key));
      if(cmp==0) {
        present->value=const_cast<ValueType*>(&value);
        return;
      } else if(cmp<0) {
        if(IsAvailable(present->left))  present=present->left;
        else {
          present->left=new BTreeNode<KeyType,ValueType>;
          present->left->key=const_cast<KeyType*>(&key);
          present->left->value=const_cast<ValueType*>(&value);
          present->left->keystate=Reference;
          present->left->valuestate=Reference;
          present->left->parent=present;
          present->left->branch=LeftBranch;
          return;
        }
      } else {
        if(IsAvailable(present->right)) present=present->right;
        else {
          present->right=new BTreeNode<KeyType,ValueType>;
          present->right->key=const_cast<KeyType*>(&key);
          present->right->value=const_cast<ValueType*>(&value);
          present->right->keystate=Reference;
          present->right->valuestate=Reference;
          present->right->parent=present;
          present->right->branch=RightBranch;
          return;
        }
      }
    }
    destBT.root=new BTreeNode<KeyType,ValueType>;
    destBT.root->key=const_cast<KeyType*>(&key);
    destBT.root->value=const_cast<ValueType*>(&value);
    destBT.root->keystate=Reference;
    destBT.root->valuestate=Reference;
  }

  template <typename KeyType, typename ValueType>
  const ValueType* get(
      const BTree<KeyType,ValueType>& BT, const KeyType& key) {
    const BTreeNode<KeyType,ValueType>* BN=getNode(BT,key);
    return (IsAvailable(BN)?BN->value:NULL);
  }

  template <typename KeyType, typename ValueType>
  const BTreeNode<KeyType,ValueType>* getNode(
      const BTree<KeyType,ValueType>& BT, const KeyType& key) {
    BTreeNode<KeyType,ValueType> *present;
    int cmp;
    present=BT.root;
    while(IsAvailable(present)) {
      cmp=compare(key,*(present->key));
      if(cmp==0)      break;
      else if(cmp<0)  present=present->left;
      else            present=present->right;
    }
    return present;
  }

  template <typename KeyType, typename ValueType>
  void removeNode(BTree<KeyType,ValueType>& BT, const KeyType& key) {
    const BTreeNode<KeyType,ValueType> *BN=getNode(BT,key);
    removeNode(BT,BN);
  }

  template <typename KeyType, typename ValueType>
  void removeNode(BTree<KeyType,ValueType>& BT,
                  const BTreeNode<KeyType,ValueType>* iBN){
    BTreeNode<KeyType,ValueType> *BN;
    BN=const_cast<BTreeNode<KeyType,ValueType>*>(iBN);
    assert(BN==getNode(BT,*(BN->key)));
    if(IsAvailable(BN)) {
      if(!IsAvailable(BN->left)) {
        if(IsAvailable(BN->parent)) {
          if(BN->branch==LeftBranch)  BN->parent->left=BN->right;
          else if(BN->branch==RightBranch)  BN->parent->right=BN->right;
          else myError("Improper Branch Flag");
        } else BT.root=BN->right;
        BN->right=NULL;
      } else if(!IsAvailable(BN->right)) {
        if(IsAvailable(BN->parent)) {
          if(BN->branch==LeftBranch)  BN->parent->left=BN->left;
          else if(BN->branch==RightBranch)  BN->parent->right=BN->left;
          else myError("Improper Branch Flag");
        } else BT.root=BN->left;
        BN->left=NULL;
      } else {
        BTreeNode<KeyType,ValueType> *movenode;
        movenode=BN->right;
        while(IsAvailable(movenode->left))  movenode=movenode->left;
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
        } else BT.root=movenode;
        movenode->left=BN->left;  BN->left=NULL;
        movenode->right=BN->right;  BN->right=NULL;
      }
    }
    safe_delete(BN);
  }

}

#endif

