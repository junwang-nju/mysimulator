
#ifndef _Interaction_Centroid_Centroid_Harmonic_H_
#define _Interaction_Centroid_Centroid_Harmonic_H_

#include "operation/interaction/centroid-centroid-base.h"
#include "operation/functional/harmonic.h"

namespace std {

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void EFuncCentroidCentroidHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    EFuncCentroidCentroidBase(X,idx,P,B,Geo,Energy,tmvec,FuncHarmonic);
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void GFuncCentroidCentroidHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    GFuncCentroidCentroidBase(X,idx,P,B,Geo,Gradient,tmvec,DiffHarmonic);
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void BFuncCentroidCentroidHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    BFuncCentroidCentroidBase(X,idx,P,B,Geo,Energy,Gradient,tmvec,BothHarmonic);
  }

}

#endif
