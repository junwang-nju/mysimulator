
#ifndef _Chain_Node_Allocate_H_
#define _Chain_Node_Allocate_H_

#include "chain/node/interface.h"
#include "object/allocate.h"

namespace mysimulator {

  template <typename T>
  void imprint(ChainNode<T>& N, const ChainNode<T>& cN) {
    assert(IsValid(cN));
    release(N);
    imprint(N.content,cN.content);
  }

}

#endif

