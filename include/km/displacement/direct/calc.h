
#ifndef _Displacement_Direct_Calc_H_
#define _Displacement_Direct_Calc_H_

#include "array-numeric/interface.h"

namespace mysimulator {

  template <typename T,typename T2,typename T3>
  void DisplacementCalcDirect(
      ArrayNumeric<T>& A,const ArrayNumeric<T1>& A1,const ArrayNumeric<T2>& A2){
    A.Copy(A1);
    A.NegShift(A2);
  }

}

#endif

