
#ifndef _Binary_Tree_Copy_H_
#define _Binary_Tree_Copy_H_

#include "btree/interface.h"
#include "btree/node/allocate.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  void _copy(Object<BTreeNode<KeyType,ValueType> >& C,
             const Object<BTreeNode<KeyType,ValueType> >& present,
             const Object<BTreeNode<KeyType,ValueType> >& parent,
             const BranchName& pbranch) {
    release(C);
    if(IsValid(present)) {
      allocate(C);
      allocate(C());
      copy(C,present);
      refer(C().parent,parent);
      C().workBranch=pbranch;
      if(IsValid(present().left))
        _copy(C().left,present().left,C,LeftBranch);
      if(IsValid(present().right))
        _copy(C().right,present().right,C,RightBranch);
    }
  }

  template <typename KeyType, typename ValueType>
  void copy(BTree<KeyType,ValueType>& B,
            const BTree<KeyType,ValueType>& cB) {
    release(B);
    _copy(B.root,cB.root,
          Object<BTreeNode<KeyType,ValueType> >(),Unassigned);
  }

}

#endif

