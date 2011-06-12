
#ifndef _Boundary_PeriodicBox_Copy_H_
#define _Boundary_PeriodicBox_Copy_H_

#include "boundary/periodic-box/interface.h"
#include "vector/copy.h"

namespace mysimulator {

  template <typename T, typename cT>
  void copy(PeriodicBox<T>& B, const PeriodicBox<cT>& cB) {
    assert(IsValid(B)&&IsValid(cB));
    copy(B.box,cB.box);
    copy(B.hbox,cB.hbox);
    copy(B.flag,cB.flag);
  }

}

#endif

