
#ifndef _Interaction_Centroid_Anchor_Point_Harmonic_H_
#define _Interaction_Centroid_Anchor_Point_Harmonic_H_

#include "operation/interaction/centroid-anchor-point-base.h"
#include "operation/functional/harmonic.h"

namespace std {
  
  template <typename T, template<typename> class DBuffer, typename GeomType>
  void EFuncCentroidAnchorPointHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    EFuncCentroidAnchorPointBase(X,idx,P,B,Geo,Energy,tmvec,FuncHarmonic);
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void GFuncCentroidAnchorPointHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    GFuncCentroidAnchorPointBase(X,idx,P,B,Geo,Gradient,tmvec,DiffHarmonic);
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void BFuncCentroidAnchorPointHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    BFuncCentroidAnchorPointBase(X,idx,P,B,Geo,Energy,Gradient,tmvec,BothHarmonic);
  }

}

#endif
