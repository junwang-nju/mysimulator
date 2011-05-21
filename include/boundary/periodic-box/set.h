
#ifndef _Boundary_PeriodicBox_Set_H_
#define _Boundary_PeriodicBox_Set_H_

#include "boundary/periodic-box/interface.h"
#include "vector/fill.h"

namespace mysimulator {

  template <typename T, typename TD>
  void set(PeriodicBox<T>& B, const Vector<TD>& box, const bool flag=true) {
    assert(IsValid(B)&&IsValid(box));
    copy(B.box,box);
    fill(B.flag,flag);
    B.synchronize();
  }

  template <typename T, typename TD, typename TF>
  void set(PeriodicBox<T>& B, const Vector<TD>& box, const Vector<TF>& flag) {
    assert(IsValid(B)&&IsValid(box)&&IsValid(flag));
    copy(B.box,box);
    copy(B.flag,flag);
    B.synchronize();
  }

}

#endif

