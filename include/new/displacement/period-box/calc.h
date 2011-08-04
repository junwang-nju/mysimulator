
#ifndef _Displacement_PeriodBox_Calc_H_
#define _Displacement_PeriodBox_Calc_H_

#include "displacement/direct/calc.h"
#include "boundary/period-box/vector-in-central.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3, typename T4>>
  void DisplacementCalc(Array1DContent<T1>& A, const Array1DContent<T2>& B,
                        const Array1DContent<T3>& C, const PeriodBox<T4>& PB) {
    DisplacementCalcDirect(A,B,C);
    shift2central(A,PB);
  }

}

#endif

