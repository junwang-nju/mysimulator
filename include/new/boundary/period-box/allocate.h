
#ifndef _Boundary_PeriodBox_Allocate_H_
#define _Boundary_PeriodBox_Allocate_H_

#include "boundary/period-box/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(PeriodBox<T>& B, const unsigned int& dim) {
    release(B);
    allocate(B.box,dim);
    allocate(B.hbox,dim);
    allocate(B.pdflag,dim);
  }

  template <typename T>
  void imprint(PeriodBox<T>& B, const PeriodBox<T>& cB) {
    assert(IsValid(cB));
    allocate(B,cB.dimension());
  }

}

#endif

