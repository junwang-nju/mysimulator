
#ifndef _Displacement_Direct_Calc_H_
#define _Displacement_Direct_Calc_H_

#include "array/1d/content/copy.h"
#include "array/1d/content/_shift_two.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3>
  void DisplacementCalcDirect(Array1DContent<T1>& A,const Array1DContent<T2>& B,
                              const Array1DContent<T3>& C) {
    unsigned int n=A.size;
    n=(n<B.size?n:B.size);
    n=(n<C.size?n:C.size);
    copy(A,B,n);
    shift(A,-cOne,C,n);
  }


}

#endif

