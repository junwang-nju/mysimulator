
#ifndef _Geometry_Displacement_PeriodicBox_Calculate_H_
#define _Geometry_Displacement_PeriodicBox_Calculate_H_

#include "geometry/displacement/direct/calc.h"
#include "boundary/periodic-box/interface.h"

namespace mysimulator {

  template <typename TA, typename TB, typename T, typename TP>
  void DisplacementCalc(
      const TA* a, const TB* b, const T* v, const unsigned int n,
      const PeriodicBox<TP>& B, const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int off=iZero, const long step=lOne) {
    DisplacementCalcDirect(a,b,v,n,aoff,astep,boff,bstep,off,step);
    B.vectorNormalize(v,n,off,step);
  }

  template <typename TA, typename TB, typename T, typename TP>
  void DisplacementCalc(
      const Vector<TA>& a, const Vector<TB>& b, Vector<T>& v,
      const PeriodicBox<TP>& B) {
    unsigned int n;
    n=(a.size<b.size?a.size:b.size);
    n=(n<v.size?n:v.size);
    DisplacementCalc(a.pdata,b.pdata,v.pdata,n,B);
  }

}

#endif

