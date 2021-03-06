
#ifndef _Interaction_Pairwise_Harmonic_H_
#define _Interaction_Pairwise_Harmonic_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/harmonic.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncHarmonic);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffHarmonic);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothHarmonic);
  }

}

#endif

