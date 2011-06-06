
#ifndef _Chain_Node_Refer_H_
#define _Chain_Node_Refer_H_

#include "chain/node/interface.h"
#include "referable-object/refer.h"

namespace mysimulator {

  template <typename T>
  void refer(ChainNode<T>& N, const ChainNode<T>& rN) {
    release(N);
    if(IsValid(rN.parent))  refer(N.parent,rN.parent);
    if(IsValid(rN.child))   refer(N.child,rN.child);
    if(IsValid(rN))         refer(N.content,rN.content);
  }

}

#endif

