
#ifndef _Chain_Node_Allocate_H_
#define _Chain_Node_Allocate_H_

#include "chain/node/interface.h"
#include "referable-object/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(ChainNode<T>& N) {
    release(N);
    allocate(N.content);
  }

  template <typename T>
  void imprint(ChainNode<T>& N, const ChainNode<T>&) { allocate(N); }

}

#endif

