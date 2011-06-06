
#ifndef _Chain_Node_Interface_H_
#define _Chain_Node_Interface_H_

#include "referable-object/interface.h"

namespace mysimulator {

  template <typename T>
  struct ChainNode {

    typedef ChainNode<T>    Type;

    Object<Type> parent;
    Object<Type> child;
    Object<T> content;

    ChainNode() : parent(), child(), content() {}
    ChainNode(const Type&) { Error("Copier of ChainNode Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for ChainNode Disabled!");
      return *this;
    }
    ~ChainNode() { clearData(); }

    void clearData() {
      release(parent);
      release(child);
      release(content);
    }
    T& operator()() { assert(IsValid(*this)); return content(); }
    const T& operator()() const { assert(IsValid(*this)); return content(); }

  };

  template <typename T>
  bool IsValid(const ChainNode<T>& N) { return IsValid(N.content); }
  template <typename T>
  void release(ChainNode<T>& N) { N.clearData(); }

}

#endif

