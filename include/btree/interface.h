
#ifndef _Binary_Tree_Interface_H_
#define _Binary_Tree_Interface_H_

#include "btree/node/interface.h"
#include "referable-object/compare.h"
#include "referable-object/copy.h"
#include "generic/release.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  struct BTree {

    typedef BTree<KeyType,ValueType>  Type;

    BTreeNode<KeyType,ValueType>  *proot;

    BTree() : proot(NULL) {}
    BTree(const Type&) { Error("Copier of BTree Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for BTree Disabled!");
      return *this;
    }
    ~BTree() { clearData(); }

    void clearData() { release(proot); }
    void insert(const KeyType& key, const ValueType& value,
                const ObjectStateName& kflag=Allocated,
                const ObjectStateName& vflag=Allocated) {
      BTreeNode<KeyType,ValueType> *present=proot;
      int cmp;
      bool kadd,vadd;
      while(true) {
        cmp=0;
        if(IsValid(present)) { cmp=compare(key,present->key); COut<<key<<"\t"<<present->key()<<"\t"<<cmp<<Endl; }
        kadd=vadd=false;
        if(cmp==0) {
          if(IsValid(present)) Warn("Same Key is met in inserting of BTree!");
          else {
            proot=new BTreeNode<KeyType,ValueType>;
            present=proot;
            kadd=true;
            present->parent=NULL;
            present->workBranch=Unassigned;
          }
          vadd=true;
        } else if(cmp<0) {
          COut<<"---- "<<key<<Endl;
          if(!IsValid(present->left)) {
            present->left=new BTreeNode<KeyType,ValueType>;
            kadd=vadd=true;
            present->left->parent=present;
            present->left->workBranch=LeftBranch;
          }
          present=present->left;
        } else {
          if(!IsValid(present->right)) {
            present->right=new BTreeNode<KeyType,ValueType>;
            kadd=vadd=true;
            present->right->parent=present;
            present->right->workBranch=RightBranch;
          }
          present=present->right;
        }
        if(kadd) copy(present->key,key,kflag);
        if(vadd) {
          copy(present->value,value,vflag);
          break;
        }
      }
    }

    const BTreeNode<KeyType,ValueType>* _getNode(const KeyType& key) const {
      BTreeNode<KeyType,ValueType> *present=proot;
      int cmp;
      while(IsValid(present)) {
        cmp=compare(key,present->key);
        if(cmp==0)      break;
        else if(cmp<0)  present=present->left;
        else            present=present->right;
      }
      return present;
    }
    const ValueType* getValue(const KeyType& key) {
      const BTreeNode<KeyType,ValueType>* pN=_getNode(key);
      return IsValid(pN)?pN->value.pdata:NULL;
    }

    void _remove(const BTreeNode<KeyType,ValueType>* pN) {
      BTreeNode<KeyType,ValueType> *present;
      present=const_cast<BTreeNode<KeyType,ValueType>*>(pN);
      if(!IsValid(pN))  return;
      assert(IsValid(*pN)&&(pN==_getNode(pN->key())));
      if(!IsValid(present->left)) {
        if(IsValid(present->parent)) {
          if(present->workBranch==LeftBranch)
            present->parent->left=present->right;
          else if(present->workBranch==RightBranch)
            present->parent->right=present->right;
          else Error("Improper Branch Flag in node!");
        } else proot=present->right;
        present->right=NULL;
      } else if(!IsValid(present->right)) {
        if(IsValid(present->parent)) {
          if(present->workBranch==LeftBranch)
            present->parent->left=present->left;
          else if(present->workBranch==RightBranch)
            present->parent->right=present->left;
          else Error("Improper Branch Flag in node!");
        } else proot=present->left;
        present->left=NULL;
      } else {
        BTreeNode<KeyType,ValueType> *mvNode;
        mvNode=present->right;
        while(IsValid(mvNode->left))  mvNode=mvNode->left;
        if(mvNode->workBranch==LeftBranch)
          mvNode->parent->left=mvNode->right;
        else if(mvNode->workBranch==RightBranch)
          mvNode->parent->right=mvNode->right;
        else Error("Improper Branch Flag in node!");
        if(IsValid(mvNode->right)) {
          mvNode->right->parent=mvNode->parent;
          mvNode->right->workBranch=mvNode->workBranch;
        }
        mvNode->parent=present->parent;
        mvNode->workBranch=present->workBranch;
        if(IsValid(mvNode->parent)) {
          if(mvNode->workBranch==LeftBranch)       mvNode->parent->left=mvNode;
          else if(mvNode->workBranch==RightBranch) mvNode->parent->right=mvNode;
          else Error("Improper Branch Flag in node!");
        } else proot=mvNode;
        mvNode->left=present->left;     present->left=NULL;
        mvNode->right=present->right;   present->right=NULL;
      }
      release(present);
    }
    void remove(const KeyType& key) {
      const BTreeNode<KeyType,ValueType>* pN=_getNode(key);
      _remove(pN);
    }

  };

  template <typename KeyType, typename ValueType>
  bool IsValid(const BTree<KeyType,ValueType>& T) { return IsValid(T.root); }

  template <typename KeyType, typename ValueType>
  void release(BTree<KeyType,ValueType>& T) { T.clearData(); }

}

#endif

