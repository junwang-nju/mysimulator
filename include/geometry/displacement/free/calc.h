
#ifndef _Geometry_Displacement_FreeSpace_Calculate_H_
#define _Geometry_Displacement_FreeSpace_Calculate_H_

#include "geometry/displacement/direct/calc.h"
#include "boundary/free/interface.h"

namespace mysimulator {

  template <typename TA, typename TB, typename T>
  void DisplacementCalc(
      const TA* a, const TB* b, T* v, const unsigned int n, const FreeSpace&,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int off=iZero,  const long step=lOne) {
    DisplacementCalcDirect(a,b,v,n,aoff,astep,boff,bstep,off,step);
  }

  template <typename TA, typename TB, typename T>
  void DisplacementCalc(
      const Vector<TA>& a,const Vector<TB>& b,Vector<T>& v,const FreeSpace&) {
    DisplacementCalcDirect(a,b,v);
  }

}

#endif

