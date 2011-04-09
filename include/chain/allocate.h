
#ifndef _Chain_Allocate_H_
#define _Chain_Allocate_H_

#include "chain/interface.h"
#include "chain/node/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(Chain<T>& C) {
    release(C);
    allocate(C.root);
    allocate(C.head);
    refer(C.root.child,C.head);
    refer(C.head.parent,C.root);
  }

  template <typename T>
  void imprint(Chain<T>& C, const Chain<T>&) { allocate(C); }

}

#endif

