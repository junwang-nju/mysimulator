
#ifndef _Binary_Tree_Interface_H_
#define _Binary_Tree_Interface_H_

#include "btree/node/interface.h"
#include "referable-object/compare.h"
#include "referable-object/copy.h"
#include "referable-object/swap.h"
#include "referable-object/mirror.h"
#include "generic/release.h"
#include "generic/exchange.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  struct BTree {

    typedef BTree<KeyType,ValueType>  Type;

    Object<BTreeNode<KeyType,ValueType> >  root;

    BTree() : root() {}
    BTree(const Type&) { Error("Copier of BTree Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for BTree Disabled!");
      return *this;
    }
    ~BTree() { clearData(); }

    void clearData() { release(root); }
    void insert(const KeyType& key, const ValueType& value,
                const ObjectStateName& kflag=Allocated,
                const ObjectStateName& vflag=Allocated) {
      Object<BTreeNode<KeyType,ValueType> > present;
      refer(present,root);
      int cmp;
      bool kadd,vadd;
      while(true) {
        cmp=0;
        if(IsValid(present)) { cmp=compare(key,present().key); }
        kadd=vadd=false;
        if(cmp==0) {
          if(IsValid(present)) Warn("Same Key is met in inserting of BTree!");
          else {
            allocate(root);
            refer(present,root);
            kadd=true;
            present().workBranch=Unassigned;
          }
          vadd=true;
        } else if(cmp<0) {
          if(!IsValid(present().left)) {
            allocate(present().left);
            kadd=vadd=true;
            refer(present().left().parent,present);
            present().left().workBranch=LeftBranch;
          }
          refer(present,present().left);
        } else {
          if(!IsValid(present().right)) {
            allocate(present().right);
            kadd=vadd=true;
            refer(present().right().parent,present);
            present().right().workBranch=RightBranch;
          }
          refer(present,present().right);
        }
        if(kadd) copy(present().key,key,kflag);
        if(vadd) {
          copy(present().value,value,vflag);
          break;
        }
      }
    }

    const BTreeNode<KeyType,ValueType>* _getNode(const KeyType& key) const {
      assert(IsValid(key));
      Object<BTreeNode<KeyType,ValueType> > present;
      refer(present,root);
      int cmp;
      while(IsValid(present)) {
        cmp=compare(key,present().key);
        if(cmp==0)      break;
        else if(cmp<0)  refer(present,present().left);
        else            refer(present,present().right);
      }
      return present.pdata;
    }
    const ValueType* getValue(const KeyType& key) {
      const BTreeNode<KeyType,ValueType>* pN=_getNode(key);
      return IsValid(pN)?pN->value.pdata:NULL;
    }

    void _remove(const BTreeNode<KeyType,ValueType>* pN) {
      if(!IsValid(pN))  return;
      Object<BTreeNode<KeyType,ValueType> > present;
      refer(present,*pN);
      assert(IsValid(present())&&(pN==_getNode(present().key())));
      if(!IsValid(present().left)) {
        if(IsValid(present().parent)) {
          if(present().workBranch==LeftBranch)
            swap(present().parent().left,present().right);
          else if(present().workBranch==RightBranch)
            swap(present().parent().right,present().right);
          else Error("Improper Branch Flag in node!");
        } else swap(root,present().right);
        present().right.flag=Referred;
      } else if(!IsValid(present().right)) {
        if(IsValid(present().parent)) {
          if(present().workBranch==LeftBranch)
            swap(present().parent().left,present().left);
          else if(present().workBranch==RightBranch)
            swap(present().parent().right,present().left);
          else Error("Improper Branch Flag in node!");
        } else swap(root,present().left);
        present().left.flag=Referred;
      } else {
        Object<BTreeNode<KeyType,ValueType> > mvNode;
        refer(mvNode,present().right);
        while(IsValid(mvNode().left))  refer(mvNode,mvNode().left);
        if(mvNode().workBranch==LeftBranch)
          mirror(mvNode().parent().left,mvNode().right);
        else if(mvNode().workBranch==RightBranch)
          mirror(mvNode().parent().right,mvNode().right);
        else Error("Improper Branch Flag in node!");
        if(IsValid(mvNode().right)) {
          swap(mvNode().right().parent,mvNode().parent);
          mvNode().right().workBranch=mvNode().workBranch;
        }
        mvNode().parent.flag=Referred;
        mvNode().right.flag=Referred;
        release(mvNode().parent);
        release(mvNode().left);
        release(mvNode().right);
        swap(mvNode().parent,present().parent);

        exchange(mvNode().workBranch,present().workBranch);
        //exchange(reinterpret_cast<int&>(mvNode().workBranch),
        //         reinterpret_cast<int&>(present().workBranch));
        swap(mvNode().left,present().left);
        swap(mvNode().right,present().right);
        if(IsValid(mvNode().left))  refer(mvNode().left().parent,mvNode);
        if(IsValid(mvNode().right)) refer(mvNode().right().parent,mvNode);
        if(IsValid(mvNode().parent)) {
          if(mvNode().workBranch==LeftBranch)
            swap(mvNode().parent().left,mvNode);
          else if(mvNode().workBranch==RightBranch)
            swap(mvNode().parent().right,mvNode);
          else Error("Improper Branch Flag in node!");
        } else swap(root,mvNode);
        release(mvNode);
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

