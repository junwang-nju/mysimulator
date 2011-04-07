
#ifndef _Chain_Node_Copy_H_
#define _Chain_Node_Copy_H_

#include "chain/node/interface.h"
#include "generic/copy.h"

namespace mysimulator {

  template <typename T>
  void copy(ChainNode<T>& N, const ChainNode<T>& cN) { copy(N(),cN()); }

}

#endif

