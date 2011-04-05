
#ifndef _Binary_Tree_Copy_H_
#define _Binary_Tree_Copy_H_

#include "btree/interface.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  void _copy(BTreeNode<KeyType,ValueType>*& C,
             const BTreeNode<KeyType,ValueType>* present,
             const BTreeNode<KeyType,ValueType>* parent,
             const BranchName& pbranch) {
    release(C);
    if(IsValid(present)) {
      C=new BTreeNode<KeyType,ValueType>;
      allocate(*C);
      copy(*C,*present);
      C->parent=const_cast<BTreeNode<KeyType,ValueType>*>(parent);
      C->workBranch=pbranch;
      if(IsValid(present->left))  _copy(C->left,present->left,C,LeftBranch);
      if(IsValid(present->right)) _copy(C->right,present->right,C,RightBranch);
    }
  }

  template <typename KeyType, typename ValueType>
  void copy(BTree<KeyType,ValueType>& B,
            const BTree<KeyType,ValueType>& cB) {
    release(B);
    _copy(B.proot,cB.proot,
          static_cast<const BTreeNode<KeyType,ValueType>*>(NULL),Unassigned);
  }

}

#endif

