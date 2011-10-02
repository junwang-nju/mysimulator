
#ifndef _MultiNode_Tree_Interface_H_
#define _MultiNode_Tree_Interface_H_

#include "multinode-tree/node/interface.h"
#include "intrinsic-type/release.h"

namespace mysimulator {

  template <typename T>
  struct MTree {
    public:
      typedef MTree<T>  Type;

      MTreeNode<T>* root;

      MTree() : root(NULL) {}
      ~MTree() { clearData(); }

      void clearData() { delete_pointer(root); }
      bool isvalid() const { return IsValid(root); }

    private:

      MTree(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(MTree<T>& MT) { T.clearData(); }

  template <typename T>
  bool IsValid(const MTree<T>& MT) { return MT.isvalid(); }

}

#endif

