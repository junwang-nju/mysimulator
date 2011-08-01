
#ifndef _Binary_Tree_Node_Interface_H_
#define _Binary_Tree_Node_Interface_H_

#include "binary-tree/branch-name.h"
#include "object/interface.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  struct BTreeNode {

    public:

      typedef BTreeNode<KeyType,ValueType>    Type;

      Object<KeyType> key;
      Object<ValueType> value;
      Type* parent;
      Type* left;
      Type* right;
      BTreeBranchName wTree;

      BTreeNode() : key(), value(), parent(NULL), left(NULL), right(NULL),
                    wTree(UnassignedBranch) {}
      ~BTreeNode() {  clearData(); }

      void clearData() {
        release(key); release(value);
        parent=NULL;  left=NULL;    right=NULL;
        wTree=UnassignedBranch;
      }
      bool isvalid() const { return IsValid(key)&&IsValid(value); }

    private:

      BTreeNode(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename KType, typename VType>
  bool IsValid(const BTreeNode<KType,VType>& N) { return N.isvalid(); }

  template <typename KType, typename VType>
  void release(BTreeNode<KType,VType>& N) { N.clearData(); }

}

#endif

