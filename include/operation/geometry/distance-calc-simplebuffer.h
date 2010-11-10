
#ifndef _Distance_Calculate_SimpleBuffer_H_
#define _Distance_Calculate_SimpleBuffer_H_

#include "operation/geometry/distance-calc.h"
#include "data/geometry/distance-buffer-simple.h"

namespace std {

  template <typename TA, typename TB, typename TD, typename GeomType>
  TD Distance(const TA* va, const TB* vb,
              const unsigned int aid, const unsigned int bid, 
              const unsigned int dim,
              const GeomType& Geo, DistanceBufferSimple<TD>& B,
              const int aoff=iZero, const long astep=lOne,
              const int boff=iZero, const long bstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    assert(IsAvailable(B));
    B.DistanceSquare()=
    Distance(va,vb,B.DisplaceVec.data,dim,Geo,aoff,astep,boff,bstep);
    return B.DistanceSquare();
  }

  template <typename TA, typename TB, typename TD, typename GeomType>
  TD Distance(const Vector<TA>& va, const Vector<TB>& vb,
              const unsigned int aid, const unsigned int bid,
              const GeomType& Geo, DistanceBufferSimple<TD>& B) {
    assert(IsAvailable(va));
    assert(IsAvailable(vb));
    assert(IsAvailable(B));
    B.DistanceSquare()=Distance(va,vb,B.DisplaceVec,Geo);
    return B.DistanceSquare();
  }

}

#endif
