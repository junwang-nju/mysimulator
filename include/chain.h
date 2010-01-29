
#ifndef _Chain_H_
#define _Chain_H_

#include "chain-node.h"

namespace std {
  template <typename T>
  class Chain {
    protected:
      ChainNode<T>  Root;
      ChainNode<T>* Head;
    public:
      typedef Chain<T>  Type;
      Chain() : Root(), Head(NULL) {}
      Chain(const Type& C) { myError("Cannot create from chain"); }
      ~Chain() { clear(); }
      Type& operator=(const Type& C) {
        clear();
        ChainNode<T> *rCNode=const_cast<ChainNode<T>*>(C.Root.child());
        while(rCNode!=NULL) {
          append(rCNode->content());
          rCNode=const_cast<ChainNode<T>*>(rCNode->child());
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

