
#ifndef _Geometry_Distance_Calculate_H_
#define _Geometry_Distance_Calculate_H_

#include "geometry/displacement2distanceSQ.h"

namespace mysimulator {

  template <typename TA, typename TB, typename T, typename GeomType>
  T DistancesqCalc(
      const TA* a, const TB* b, T* v, const unsigned int n, const GeomType& G,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int off=iZero,  const long step=lOne) {
    DisplacementCalc(a,b,v,n,G,aoff,astep,boff,bstep,off,step);
    return displacement2distanceSQ(v,n,off,step);
  }

  template <typename TA, typename TB, typename T, typename GeomType>
  T DistancesqCalc(
      const Vector<TA>& a, const Vector<TB>& b, Vector<T>& v,
      const GeomType& G) {
    DisplacementCalc(a,b,v,G);
    return displacement2distanceSQ(v);
  }

}

#endif

