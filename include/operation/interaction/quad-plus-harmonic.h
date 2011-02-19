
#ifndef _Interaction_Quadruple_Plus_Harmonic_H_
#define _Interaction_Quadruple_Plus_Harmonic_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/quad-plus-harmonic.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncQuadHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncQuadHarmonic);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncQuadHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffQuadHarmonic);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncQuadHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothQuadHarmonic);
  }

}

#endif
