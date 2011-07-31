
#ifndef _Chain_Allocate_H_
#define _Chain_Allocate_H_

#include "chain/interface.h"

namespace mysimulator {

  template <typename T>
  void allocate(Chain<T>& C) {
    release(C);
    C.root.child=new ChainNode<T>;
    C.head=C.root.child;
    C.head->parent=&(C.root);
  }

}

#endif

