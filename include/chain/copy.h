
#ifndef _Chain_Copy_H_
#define _Chain_Copy_H_

#include "chain/interface.h"

namespace mysimulator {

  template <typename T>
  void copy(Chain<T>& C, const Chain<T>& cC) {
    assert(IsValid(cC));
    allocate(C);
    Object<ChainNode<T> > runNode;
    refer(runNode,cC.root);
    while(IsValid(runNode().child)&&(!IsSameObject(runNode().child,cC.head))) {
      refer(runNode,runNode().child);
      C.append(runNode().content());
    }
  }

}

#endif

