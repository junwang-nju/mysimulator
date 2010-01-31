
#include "btree.h"
#include "memory.h"

namespace std {

  template <typename KeyType, typename ValueType>
  void BTree<KeyType,ValueType>::clear() {
    NodeType *present=&Root, *tofree;
    while(true) {
      if(present->left()!=NULL) present=present->left();
      else if(present->right()!=NULL) present=present->right();
      else if(present!=&Root) {
        tofree=present;
        present=present.parent();
        remove(tofree);
      } else break;
    }
  }

  template <typename KeyType, typename ValueType>
  void BTree<KeyType,ValueType>::insert(const KeyType& K, const ValueType& V) {
    if(Root.Ptr2Key()==NULL) {
      Root.Ptr2Key()=const_cast<KeyType*>(&K);
      Root.Ptr2Value()=const_cast<ValueType*>(&V);
    } else {
      NodeType* present=&Root;
      int cmp;
      while(true) {
        cmp=compare(*(present->Ptr2Key()),K);
        if(cmp==0) {
          present->Ptr2Value()=const_cast<ValueType*>(&V);
          break;
        } else if(cmp<0) {
          if(present->left()==NULL) {
            present->SetLeft(new NodeType(K,V,present,true,NULL,NULL));
            break;
          } else  present=present->left();
        } else {
          if(present->right()==NULL) {
            present->SetRight(new NodeType(K,V,present,false,NULL,NULL));
            break;
          } else present=present->right();
        }
      }
    }
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
    safe_delete(pnd);
  }

}

