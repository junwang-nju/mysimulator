
#ifndef _Displacement_FreeSpace_Calc_H_
#define _Displacement_FreeSpace_Calc_H_

#include "displacement/direct/calc.h"
#include "boundary/free/interface.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3>
  void DisplacementCalc(Array1DContent<T1>& A, const Array1DContent<T2>& B,
                        const Array1DContent<T3>& C, const FreeSpace&) {
    DisplacementCalcDirect(A,B,C);
  }

}

#endif

