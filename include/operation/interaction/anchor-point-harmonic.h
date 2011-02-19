
#ifndef _Interaction_Anchor_Point_Harmonic_H_
#define _Interaction_Anchor_Point_Harmonic_H_

#include "operation/interaction/anchor-point-base.h"
#include "data/name/external-object-harmonic.h"
#include "operation/functional/harmonic.h"

namespace std {

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void EFuncAnchorPointHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL) {
    EFuncAnchorPointBase(X,idx,P,B,Geo,Energy,FuncHarmonic);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void GFuncAnchorPointHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    GFuncAnchorPointBase(X,idx,P,B,Geo,Gradient,DiffHarmonic);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void BFuncAnchorPointHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    BFuncAnchorPointBase(X,idx,P,B,Geo,Energy,Gradient,BothHarmonic);
  }

}

#endif

