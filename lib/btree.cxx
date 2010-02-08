
#include "btree.h"
#include "memory.h"

namespace std {

  template <typename KeyType, typename ValueType>
  BTreeNode<KeyType,ValueType>& BTree<KeyType,ValueType>::Root() {
    return *pRoot;
  }

  template <typename KeyType, typename ValueType>
  const BTreeNode<KeyType,ValueType>& BTree<KeyType,ValueType>::Root() const {
    return *pRoot;
  }

  template <typename KeyType, typename ValueType>
  void BTree<KeyType,ValueType>::clear() {
    NodeType *present=pRoot, *tofree;
    while(present!=NULL) {
      if(present->left()!=NULL) present=present->left();
      else if(present->right()!=NULL) present=present->right();
      else {
        tofree=present;
        present=present.parent();
        remove(tofree);
      }
    }
  }

  template <typename KeyType, typename ValueType>
  void BTree<KeyType,ValueType>::insert(const KeyType& K, const ValueType& V) {
    NodeType *present=pRoot;
    int cmp;
    while(present!=NULL) {
      cmp=compare(*(present->ptr2key()),K);
      if(cmp==0) {
        present->ptr2value()=const_cast<ValueType*>(&V);
        return;
      } else if(cmp<0)  {
        if(present->left()!=NULL)   present=present->left();
        else {
          present->SetLeft(new NodeType(&K,&V,present,-1,NULL,NULL,true));
          return;
        }
      } else  {
        if(present->right()!=NULL)  present=present->right();
        else {
          present->SetRight(new NodeType(&K,&V,present,1,NULL,NULL,true));
          return;
        }
      }
    }
    pRoot=new NodeType(&K,&V,NULL,0,NULL,NULL,true);
  }

  template <typename KeyType, typename ValueType>
  void BTree<KeyType,ValueType>::insert(BTreeNode<KeyType,ValueType>& nd) {
    NodeType *present=pRoot;
    int cmp,pflag=0;
    while(present!=NULL) {
      cmp=compare(*(present->ptr2key()),*(nd.ptr2key()));
      if(cmp==0) {
        myError("Conflict in the inserted Key");
        return;
      } else if(cmp<0)  {
        if(present->left()!=NULL)   present=present->left();
        else {
          present->SetLeft(&nd);
          nd.SetParent(present,-1);
          return;
        }
      } else  {
        if(present->right()!=NULL)  present=present->right();
        else {
          present->SetRight(&nd);
          nd.SetParent(present,1);
          return;
        }
      }
    }
    pRoot=&nd;
  }

  template <typename KeyType, typename ValueType>
  const ValueType* BTree<KeyType,ValueType>::get(const KeyType& K) const {
    NodeType *present=pRoot;
    int cmp;
    while(present!=NULL) {
      cmp=compare(*(present->ptr2key()),K);
      if(cmp==0)  return  present->ptr2value();
      else if(cmp<0)  present=present->left();
      else            present=present->right();
    }
    return NULL;
  }

  template <typename KeyType, typename ValueType>
  void BTree<KeyType,ValueType>::remove(BTreeNode<KeyType,ValueType>*& pnd) {
    if(pnd==NULL) return;
    NodeType *parent=pnd->parent();
    NodeType *left=pnd->left();
    NodeType *right=pnd->right();
    int pflag=pnd->WhereParentFrom();
    if(left==NULL) {
      if(pflag==0)      pRoot=right;
      else if(pflag==1) parent->SetRight(right);
      else              parent->SetLeft(right);
      if(right!=NULL)   right->SetParent(parent,pflag);
    } else if(right==NULL) {
      if(pflag==0)      pRoot=left;
      else if(pflag==1) parent->SetRight(left);
      else              parent->SetLeft(left);
      left->SetParent(parent,pflag);
    } else {
      NodeType *rnd=right;
      while(rnd->left()!=NULL)  rnd=rnd->left();
      if(rnd->WhereParentFrom()==1) rnd->parent()->SetRight(rnd->right());
      else                          rnd->parent()->SetLeft(rnd->right());
      if(rnd->right()!=NULL)
        rnd->right()->SetParent(rnd->parent(),rnd->WhereParentFrom());
      rnd->SetParent(parent,pflag);
      rnd->SetLeft(left);
      rnd->SetRight(right);
    }
    if(pnd->IsAllocByTree()) safe_delete(pnd);
  }

}

