
#ifndef _Chain_Node_H_
#define _Chain_Node_H_

#include "error-proc.h"

namespace std {

  template <typename T>
  class ChainNode {

    public:

      typedef ChainNode<T>    Type;

    protected:

      Type* Parent;

      Type* Child;

      T     Content;

      bool  AllocFg;

    public:

      ChainNode() : Parent(NULL), Child(NULL), Content(), AllocFg(false) {}

      ChainNode(const Type& CN) { myError("Cannot create from chain node"); }

      ~ChainNode() {}

      Type& operator=(const Type& CN) { Content=CN.Content; return *this; }

      template <typename inputT>
      Type& operator=(const inputT& D) { Content=D; return *this; }

      void clear() { Parent=NULL; Child=NULL; }

      Type*& parent() { return Parent; }

      const Type* parent() const { return Parent; }

      Type*& child() { return Child; }

      const Type* child() const { return Child; }

      T& content() { return Content; }

      const T& content() const { return Content; }

      const bool IsAllocByChain() const { return AllocFg; }

      void SetChainAllocFlag(const bool efg) { AllocFg=efg; }

      void add_before(Type& node) {
        Parent->Child=&node;
        node.Parent=Parent;
        node.Child=this;
        Parent=&node;
      }

      void remove_self() {
        Parent->Child=Child;
        Child->Parent=Parent;
        clear();
      }

  };

}

#endif
