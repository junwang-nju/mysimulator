
#ifndef _MultiNode_Tree_Node_Interface_H_
#define _MultiNode_Tree_Node_Interface_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  struct MTreeNode {
    public:
      typedef MTreeNode<T>  Type;

      Object<T> Val;
      Object<Type> parent;
      Array1D<Object<Type> > child;

      MTreeNode() : Val(), parent(), child() {}
      ~MTreeNode() { clearData(); }

      void clearData() { release(Val); release(parent); release(child); }
      bool isvalid() const { return IsValid(Val); }

    private:

      MTreeNode(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(MTreeNode<T>& N) { N.clearData(); }

  template <typename T>
  bool IsValid(const MTreeNode<T>& N) { return N.isvalid(); }

}

#endif

