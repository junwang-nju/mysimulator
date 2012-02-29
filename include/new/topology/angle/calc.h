
#ifndef _Topology_Angle_Calc_H_
#define _Topology_Angle_Calc_H_

#include "array/1d/allocate.h"
#include "distance/calc.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  T cosAngle(const Array1DContent<T>& XI, const Array1DContent<T>& XJ,
             const Array1DContent<T>& XK, const GeomType& Geo) {
    Array1D<T> tmvec;
    imprint(tmvec,XI);
    T dsqij,dsqjk,dsqki;
    dsqij=DistanceSQ(tmvec,XI,XJ,Geo);
    dsqjk=DistanceSQ(tmvec,XJ,XK,Geo);
    dsqki=DistanceSQ(tmvec,XK,XI,Geo);
    release(tmvec);
    return (dsqij+dsqjk-dsqki)/sqroot(dsqij*dsqjk)*0.5;
  }

}

#endif

