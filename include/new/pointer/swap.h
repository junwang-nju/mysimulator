
#ifndef _Pointer_Swap_H_
#define _Pointer_Swap_H_

#include "pointer/interface.h"
#include "intrinsic-type/exchange.h"
#include <cassert>

namespace mysimulator {

  template <typename T>
  void _Swap(Pointer<T>& p1, Pointer<T>& p2) {
    exchange(p1.ptr,p2.ptr);
    exchange(p1.state,p2.state);
    exchange(p1.parent,p2.parent);
    exchange(p1.pstate,p2.pstate);
    exchange(p1.delfunc,p2.delfunc);
  }

  /* swapping pointers of different states would confuse the system release
   * operations. Manual release is often expected.
   */
  template <typename T>
  void Swap(Pointer<T>& p1, Pointer<T>& p2) {
    assert(p1.state<=0);
    assert(p2.state<=0);
    _Swap(p1,p2);
  }

}

#endif


