
#ifndef _Displacement_FreeSpace_Calc_H_
#define _Displacement_FreeSpace_Calc_H_

#include "displacement/direct/calc.h"
#include "boundary/free/interface.h"

namespace mysimulator {

  template <typename T1,typename T2,typename T3>
  void DisplacementCalc(
      Array1D<T1>& V,const Array1D<T2>& V2,const Array1D<T3>& V3,
      const FreeSpace&,unsigned int n) {
    DisplacementCalcDirect(V,V2,V3,n);
  }

}

#endif

