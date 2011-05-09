
#ifndef _Geometry_Distance_DBufferSimple_Calculate_H_
#define _Geometry_Distance_DBufferSimple_Calculate_H_

#include "geometry/distance/direct/calc.h"
#include "buffer/distance/simple/interface.h"

namespace mysimulator {

  template <typename TA, typename TB, typename T, typename BoundType>
  T DistanceSqCalc(
      const TA* a,const TB* b,const unsigned int,const unsigned int,
      const BoundType& G, SimpleDistanceBuffer<T>& B, const unsigned int n,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne) {
    assert(IsValid(B));
    B.DistanceSquare()=
      DistanceSqCalcDirect(a,b,B.DisplaceVector.pdata,n,G,
                           aoff,astep,boff,bstep);
    return B.DistanceSquare();
  }

  template <typename TA, typename TB, typename T, typename BoundType>
  T DistanceSqCalc(
      const Vector<TA>& a, const Vector<TB>& b, const unsigned int,
      const unsigned int, const BoundType& G, SimpleDistanceBuffer<T>& B) {
    assert(IsValid(a)&&IsValid(b)&&IsValid(B));
    B.DistanceSquare()=DistanceSqCalcDirect(a,b,B.DisplaceVector,G);
    return B.DistanceSquare();
  }

}

#endif

