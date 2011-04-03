
#ifndef _Chain_Interface_H_
#define _Chain_Interface_H_

#include "chain/node/interface.h"
#include "referable-object/refer.h"
#include "referable-object/compare.h"

namespace mysimulator {

  template <typename T>
  struct Chain {

    typedef Chain<T>    Type;

    ChainNode<T> root,head;

    Chain() : root(), head() {}
    Chain(const Type&) { Error("Copier of Chain Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Chain Disabled!");
      return *this;
    }
    ~Chain() { clearData(); }

    void clearData() {};
    bool IsContained(const ChainNode<T>& N) {
      Object<ChainNode<T> > runNode;
      refer(runNode,N);
      while(IsValid(runNode.parent))  refer(runNode,runNode.parent);
      return IsSameObject(runNode,root);
    }
    void removeNode(ChainNode<T>& N) {
      assert(IsContained(N));
      bool flag;
      Object<ChainNode<T> > runNode;
      refer(runNode,N);////////
    }

  };

  template <typename T>
  void IsValid(const Chain<T>& C) { return IsValid(C.root)&&IsValid(C.head); }

  template <typename T>
  void release(Chain<T>& C) { C.clearData(); }

  template <typename T>
  void allocate(Chain<T>& C) {
    release(C);
    allocate(C.root);
    allocate(C.head);
    refer(C.root.child,C.head);
    refer(C.head.parent,C.root);
  }

}

#endif

