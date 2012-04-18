
#ifndef _Displacement_Direct_Calc_H_
#define _Displacement_Direct_Calc_H_

#include "array/1d/size.h"
#include "array/1d/copy.h"
#include "array/1d/shift.h"

namespace mysimulator {

  //assuming n is small
  template <typename T1, typename T2, typename T3>
  void DisplacementCalcDirect(T1* p, const T2* q, const T3* r, unsigned int n) {
    Copy(p,q,n);
    Shift(p,-1.,r,n);
  }

}

#endif

