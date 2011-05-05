
#ifndef _Geometry_Displacement_PeriodicBox_Calculate_H_
#define _Geometry_Displacement_PeriodicBox_Calculate_H_

#include "geometry/displacement/base/calc.h"
#include "boundary/periodic-box/interface.h"

namespace mysimulator {

  template <typename TA, typename TB, typename TD, typename T>
  void DisplacementCalc(
      const TA* a, const TB* b, TD* v, const unsigned int dim,
      const PeriodicBox<T>& B,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int doff=iZero, const long dstep=lOne) {
    DisplacementCalc(a,b,v,dim,aoff,astep,boff,bstep,doff,dstep);
    B.vectorNormalize(v,dim,doff,dstep);
  }

  template <typename TA, typename TB, typename TD, typename T>
  void DisplacementCalc(
      const Vector<TA>& a, const Vector<TB>& b, Vector<TD>& v,
      const PeriodicBox<T>& B) {
    unsigned int n;
    n=(a.size<b.size?a.size:b.size);
    n=(n<v.size?n:v.size);
    DisplacementCalc(a.pdata,b.pdata,v.pdata,n,B);
  }

}

#endif

