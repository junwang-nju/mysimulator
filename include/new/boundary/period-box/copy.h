
#ifndef _Boundary_PeriodBox_Copy_H_
#define _Boundary_PeriodBox_Copy_H_

#include "boundary/period-box/interface.h"

namespace mysimulator {

  template <typename T, typename cT>
  void copy(PeriodBox<T>& B, const PeriodBox<cT>& cB) {
    assert(IsValid(B)&&IsValid(cB));
    copy(B.box,cB.box);
    copy(B.hbox,cB.hbox);
    copy(B.flag,cB.flag);
  }

}

#endif

