
#ifndef _Boundary_PeriodicBox_Allocate_H_
#define _Boundary_PeriodicBox_Allocate_H_

#include "boundary/periodic-box/interface.h"

namespace mysimulator {

  template <typename T>
  void allocate(PeriodicBox<T>& B, const unsigned int dim) {
    allocate(B.box,dim);
    allocate(B.hbox,dim);
    allocate(B.flag,dim);
  }

}

#endif

