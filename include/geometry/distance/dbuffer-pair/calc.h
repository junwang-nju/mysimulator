
#ifndef _Geometry_Distance_DBPair_Calculate_H_
#define _Geometry_Distance_DBPair_Calculate_H_

#include "buffer/distance/pair/interface.h"
#include "geometry/distance/calc.h"

namespace mysimulator {

  template <typename TA, typename TB, typename T, typename GeomType>
  T DistanceSqCalc(
      const TA* a, const TB* b, const unsigned int ida, const unsigned int idb,
      const GeomType& G, PairDistanceBuffer<T>& B, const unsigned int dim,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne) {
    assert(IsValid(B));
    if(IsNewest(B.DSqMat,ida,idb)) {
      B.DistanceSquare()=B.DSqMat.value(ida,idb);
      DisplacementCalc(a,b,B.DisplaceVector.pdata,dim,G,aoff,astep,boff,bstep);
    } else {
      B.DistanceSquare()=
        DistanceSqCalc(a,b,B.DisplaceVector.pdata,dim,G,aoff,astep,boff,bstep);
      B.DSqMat.renew(ida,idb,B.DistanceSquare());
    }
    return B.DistanceSquare();
  }

  template <typename TA, typename TB, typename T, typename GeomType>
  T DistanceSqCalc(
      const Vector<TA>& a, const Vector<TB>& b, const unsigned int ida,
      const unsigned int idb, const GeomType& G, PairDistanceBuffer<T>& B) {
    assert(IsValid(a)&&IsValid(b)&&IsValid(B));
    if(IsNewest(B.DSqMat,ida,idb)) {
      B.DistanceSquare()=B.DSqMat.value(ida,idb);
      DisplacementCalc(a,b,B.DisplaceVector,G);
    } else {
      B.DistanceSquare()=DistanceSqCalc(a,b,B.DisplaceVector,G);
      B.DSqMat.renew(ida,idb,B.DistanceSquare());
    }
    return B.DistanceSquare();
  }

}

#endif

