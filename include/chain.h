
#ifndef _Chain_H_
#define _Chain_H_

#include "chain-node.h"

namespace std {
  template <typename T>
  class Chain {
    public:
      typedef Chain<T>  Type;
      typedef ChainNode<T> NodeType;
    protected:
      NodeType  Root;
      NodeType  Head;
    public:
      Chain() : Root(), Head() { Root.child()=&Head; Head.parent()=&Root; }
      Chain(const Type& C) { myError("Cannot create from chain"); }
      ~Chain() { clear(); }
      Type& operator=(const Type& C) {
        clear();
        NodeType *pCNode=const_cast<NodeType*>(C.Root.child());
        while(pCNode!=&(C.Head)) {
          append(pCNode->content());
          pCNode=const_cast<NodeType*>(pCNode->child());
        }
        return *this;
      }
      void clear();
      void append(const T& content);
      void append(ChainNode<T>& node);
      void remove(ChainNode<T>*& pnode);
  };
}

#endif

