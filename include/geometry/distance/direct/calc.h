
#ifndef _Geometry_Distance_Direct_Calculate_H_
#define _Geometry_Distance_Direct_Calculate_H_

#include "geometry/displacement-2-distanceSq.h"

namespace mysimulator {

  template <typename TA, typename TB, typename T, typename BoundType>
  T DistanceSqCalcDirect(
      const TA* a,const TB* b,T* v,const unsigned int n,const BoundType& B,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int off=iZero,  const long step=lOne) {
    DisplacementCalc(a,b,v,n,B,aoff,astep,boff,bstep,off,step);
    return displacement2distanceSq(v,n,off,step);
  }

  template <typename TA, typename TB, typename T, typename BoundType>
  T DistanceSqCalcDirect(
      const Vector<TA>& a,const Vector<TB>& b,Vector<T>& v,const BoundType& B) {
    DisplacementCalc(a,b,v,B);
    return displacement2distanceSq(v);
  }

}

#endif


