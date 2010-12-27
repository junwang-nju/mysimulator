
#ifndef _Interaction_Particle_Centroid_Harmonic_H_
#define _Interaction_Particle_Centroid_Harmonic_H_

#include "operation/interaction/particle-centroid-base.h"
#include "operation/functional/harmonic.h"

namespace std {

  template <typename T,template <typename> class DBuffer, typename GeomType>
  void EFuncParticleCentroidHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    EFuncParticleCentroidBase(X,idx,P,B,Geo,Energy,tmvec,FuncHarmonic);
  }

  template <typename T,template <typename> class DBuffer, typename GeomType>
  void GFuncParticleCentroidHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    GFuncParticleCentroidBase(X,idx,P,B,Geo,Gradient,tmvec,DiffHarmonic);
  }

  template <typename T,template <typename> class DBuffer, typename GeomType>
  void BFuncParticleCentroidHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    BFuncParticleCentroidBase(X,idx,P,B,Geo,Energy,Gradient,tmvec,BothHarmonic);
  }

}

#endif
