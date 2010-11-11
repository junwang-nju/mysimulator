
#ifndef _Distance_Calculate_Buffer_PairStorage_H_
#define _Distance_Calculate_Buffer_PairStorage_H_

#include "data/geometry/distance-buffer-pairstorage.h"
#include "operation/geometry/distance-calc.h"

namespace std {

  template <typename TA, typename TB, typename TD, typename GeomType>
  TD Distance(const TA* va, const TB* vb,
              const unsigned int aid, const unsigned int bid, 
              const unsigned int dim,
              const GeomType& Geo, DistanceBufferPairStorage<TD>& B,
              const int aoff=iZero, const long astep=lOne,
              const int boff=iZero, const long bstep=lOne,
              const int doff=iZero, const long dstep=lOne) {
    if(IsUptodate(B.DsqMat,aid,bid)) {
      B.DistanceSquare()=B.DsqMat(aid,bid).content;
      Displace(va,vb,B.DisplaceVec.data,dim,Geo,
               aoff,astep,boff,bstep,doff,dstep);
    } else {
      B.DistanceSquare()=Distance(va,vb,B.DisplaceVec.data,dim,Geo,
                                  aoff,astep,boff,bstep,doff,dstep);
      B.updateItem(aid,bid,B.DistanceSquare());
    }
    return B.DistanceSquare();
  }

  template <typename TA, typename TB, typename TD, typename GeomType>
  TD Distance(const Vector<TA>& va, const Vector<TB>& vb,
              const unsigned int aid, const unsigned int bid,
              const GeomType& Geo, DistanceBufferPairStorage<TD>& B) {
    assert(IsAvailable(va));
    assert(IsAvailable(vb));
    assert(IsAvailable(B));
    if(IsUptodate(B.DsqMat,aid,bid)) {
      B.DistanceSquare()=B.DsqMat(aid,bid).content;
      Displacement(va,vb,B.DisplaceVec,Geo);
    } else {
      B.DistanceSquare()=Distance(va,vb,B.DisplaceVec,Geo);
      B.DsqMat.updateItem(aid,bid,B.DistanceSquare());
    }
    return B.DistanceSquare();
  }

}

#endif
