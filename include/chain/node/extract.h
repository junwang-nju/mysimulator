
#ifndef _Chain_Node_Extract_H_
#define _Chain_Node_Extract_H_

#include "referable-object/compare.h"
#include "chain/node/interface.h"

namespace mysimulator {

  template <typename T>
  ObjectStateName extract(ChainNode<T>& N) {
    swap(N.parent().child,N.child);
    swap(N.parent().child().parent,N.parent);
    ObjectStateName NState;
    NState=((N.parent.flag==Allocated)||(N.child.flag==Allocated)?
            Allocated:Referred);
    N.parent.flag=Referred;
    N.child.flag=Referred;
    return NState;
  }

}

#endif

