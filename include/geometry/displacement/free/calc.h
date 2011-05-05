
#ifndef _Gemetry_Displacement_FreeSpace_Calculate_H_
#define _Gemetry_Displacement_FreeSpace_Calculate_H_

#include "boundary/free/interface.h"
#include "geometry/displacement/base/calc.h"

namespace mysimulator {

  template <typename TA, typename TB, typename T>
  void DisplacementCalc(
      const TA* a,const TB* b,T* v,const unsigned int dim,const FreeSpace& B,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int off=iZero,  const long step=lOne) {
    DisplacementCalc(a,b,v,dim,aoff,astep,boff,bstep,off,step);
  }

  template <typename TA, typename TB, typename T>
  void DisplacementCalc(
      const Vector<TA>& a,const Vector<TB>& b,Vector<T>& v,const FreeSpace& B) {
    DisplacementCalc(va,vb,v);
  }

}

#endif

