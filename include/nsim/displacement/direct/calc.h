
#ifndef _Displacement_Direct_Calc_H_
#define _Displacement_Direct_Calc_H_

#include "array/1d/shift-copy.h"

namespace mysimulator {

  template <typename T1,typename T2,typename T3>
  void DisplacementCalcDirect(
      Array1D<T1>& V,const Array1D<T2>& V2,const Array1D<T3>& V3,
      unsigned int n) {
    NegShiftCopy(V,V2,V3,n);
  }

}

#endif

