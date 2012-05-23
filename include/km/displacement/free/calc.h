
#ifndef _Displacement_Free_Calc_H_
#define _Displacement_Free_Calc_H_

#include "displacement/direct/calc.h"
#include "boundary/free/interface.h"

namespace mysimulator {

  template <typename T, typename T1, typename T2>
  void DisplacementCalc(
      ArrayNumeric<T>& A,const ArrayNumeric<T1>& A1,const ArrayNumeric<T2>& A2,
      const FreeSpace&){
    DisplacementCalcDirect(A,A1,A2);
  }

}

#endif

