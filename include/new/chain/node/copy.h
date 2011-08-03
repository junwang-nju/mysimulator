
#ifndef _Chain_Node_Copy_H_
#define _Chain_Node_Copy_H_

#include "chain/node/interface.h"
#include "object/copy.h"

namespace mysimulator {

  template <typename T>
  void copy(ChainNode<T>& N, const ChainNode<T>& cN) {
    assert(IsValid(N)&&IsValid(cN));
    copy(N.parent,cN.parent);
    copy(N.child,cN.child);
    copy(N.content,cN.content);
  }

}

#endif

