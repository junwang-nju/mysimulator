
#ifndef _Displacement_FreeSpace_Calc_H_
#define _Displacement_FreeSpace_Calc_H_

#include "displacement/direct/calc.h"
#include "boundary/free/interface.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3>
  void DisplacementCalc(T1* p, const T2* q, const T3* r, const FreeSpace&,
                        unsigned int n) {
    DisplacementCalcDirect(p,q,r,n);
  }

}

#endif

