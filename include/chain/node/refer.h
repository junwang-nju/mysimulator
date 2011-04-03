
#ifndef _Chain_Node_Refer_H_
#define _Chain_Node_Refer_H_

#include "chain/node/interface.h"

namespace mysimulator {

  template <typename T>
  void refer(ChainNode<T>& N, const ChainNode<T>& rN) {
    assert(IsValid(rN));
    release(N);
    refer(N.parent,rN.parent);
    refer(N.child,rN.child);
    refer(N.content,rN.content);
  }

}

#endif

