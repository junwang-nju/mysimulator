
#ifndef _Geometry_Distance_DBSimple_Calculate_H_
#define _Geometry_Distance_DBSimple_Calculate_H_

#include "geometry/distance/calc.h"
#include "buffer/distance/simple/interface.h"

namespace mysimulator {

  template <typename TA, typename TB, typename T, typename GeomType>
  T DistanceSqCalc(
      const TA* a, const TB* b, const unsigned int ida, const unsigned int idb,
      const GeomType& G, SimpleDistanceBuffer<T>& B, const unsigned int dim,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne) {
    assert(IsValid(B));
    B.DistanceSquare()=
      DistanceSqCalc(a,b,B.DisplaceVector.pdata,dim,G,aoff,bstep,boff,bstep);
    return B.DistanceSquare();
  }

  template <typename TA, typename TB, typename T, typename GeomType>
  T DistanceSqCalc(
      const Vector<TA>& a, const Vector<TB>& b, const unsigned int ida,
      const unsigned int idb, const GeomType& G, SimpleDistanceBuffer<T>& B) {
    assert(IsValid(a)&&IsValid(b)&&IsValid(B));
    B.DistanceSquare()=DistanceSqCalc(a,b,B.DisplaceVector,G);
    return B.DistanceSquare();
  }

}

#endif

