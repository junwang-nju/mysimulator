
#ifndef _Chain_Node_Extract_H_
#define _Chain_Node_Extract_H_

#include "referable-object/compare.h"
#include "chain/node/interface.h"

namespace mysimulator {

  template <typename T>
  ObjectStateName extract(ChainNode<T>& N) {
    ObjectStateName NState=Referred;
    if(IsValid(N.parent)&&IsValid(N.child)) {
      swap(N.parent().child,N.child);
      swap(N.parent().child().parent,N.parent);
      NState=((N.parent.flag==Allocated)||(N.child.flag==Allocated)?
               Allocated:Referred);
      N.parent.flag=Referred;
      N.child.flag=Referred;
    } else if(IsValid(N.parent)) {
      swap(N.parent().child,N.child);
      NState=(N.child.flag==Allocated?Allocated:Referred);
    } else if(IsValid(N.child)) {
      swap(N.child().parent,N.parent);
      NState=(N.parent.flag==Allocated?Allocated:Referred);
    }
    return NState;
  }

}

#endif

