
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
      void clear();
      Type*& parent();
      const Type* parent() const;
      Type*& child();
      const Type* child() const;
      T& content();
      const T& content() const;
      const bool IsAllocByChain() const;
      void SetChainAllocFlag(bool efg);
      void add_before(Type& node);
      void remove_self();
  };
}

#endif

