
#ifndef _Boundary_PeriodicBox_Allocate_H_
#define _Boundary_PeriodicBox_Allocate_H_

#include "boundary/periodic-box/interface.h"
#include "vector/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(PeriodicBox<T>& B, const unsigned int dim) {
    allocate(B.box,dim);
    allocate(B.hbox,dim);
    allocate(B.flag,dim);
  }

  template <typename T>
  void imprint(PeriodicBox<T>& B, const PeriodicBox<T>& cB) {
    assert(IsValid(cB));
    allocate(B,cB.box.size);
  }

}

#endif

