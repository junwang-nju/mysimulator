
#ifndef _Boundary_PeriodBox_Init_H_
#define _Boundary_PeriodBox_Init_H_

#include "boundary/period-box/interface.h"
#include "array/1d/content/fill.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void set(PeriodBox<T1>& B, const Array1DContent<T2>& box, const bool fg=true){
    assert(IsValid(B)&&IsValid(box));
    copy(B.box,box);
    fill(B.pdflag,fg);
    B.sync();
  }

  template <typename T1, typename T2>
  void init(PeriodBox<T1>& B, const Array1DContent<T2>& box,
            const Array1DContent<bool>& fg) {
    assert(IsValid(B)&&IsValid(box)&&IsValid(fg));
    copy(B.box,box);
    copy(B.pdflag,fg);
    B.sync();
  }

}

#endif

