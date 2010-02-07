
#include "btree.h"
#include "memory.h"

namespace std {

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
      cmp=compare(*(present->Ptr2Key()),K);
      if(cmp==0) {
        present->Ptr2Value()=const_cast<ValueType*>(&V);
        return;
      } else if(cmp<0)  present=present->left();
      else              present=present->right();
    }
    present=new NodeType(&K,&V,NULL,0,NULL,NULL,true);
  }

  template <typename KeyType, typename ValueType>
  const ValueType* BTree<KeyType,ValueType>::get(const KeyType& K) const {
    if(Root.Ptr2Key()==NULL)  return NULL;
    NodeType *present=const_cast<NodeType*>(&Root);
    int cmp;
    while(true) {
      cmp=compare(*(present->Ptr2Key()),K);
      if(cmp==0)  return present->Ptr2Value();
      else if(cmp<0)  present=present->left();
      else            present=present->right();
      if(present==NULL)  break;
    }
    return NULL;
  }

  template <typename KeyType, typename ValueType>
  bool remove_base(BTreeNode<KeyType,ValueType>& nd) {
    if(nd.left()==NULL) {
      if(nd.IsParentFromLeft()) nd.parent()->SetLeft(nd.right());
      else                      nd.parent()->SetRight(nd.right());
      if(nd.right()!=NULL)
        nd.right()->SetParent(nd.parent(),nd.IsParentFromLeft());
    } else {
      if(nd.right()==NULL) {
        if(nd.IsParentFromLeft()) nd.parent()->SetLeft(nd.left());
        else                      nd.parent()->SetRight(nd.left());
        nd.left()->SetParent(nd.parent(),nd.IsParentFromLeft());
      } else return false;
    }
    return true;
  }

  template <typename KeyType, typename ValueType>
  void BTree<KeyType,ValueType>::remove(BTreeNode<KeyType,ValueType>*& pnd) {
    if(!remove_base(*pnd)) {
      BTreeNode<KeyType,ValueType>* rnd;
      rnd=pnd.right();
      while(rnd->left()!=NULL) rnd=rnd->left();
      remove_base(*rnd);
      rnd->SetParent(pnd->parent(),pnd->IsParentFromLeft());
      rnd->SetLeft(pnd->left());
      rnd->SetRight(pnd->right());
    }
    if(pnd->IsAllocByTree()) safe_delete(pnd);
  }

}

