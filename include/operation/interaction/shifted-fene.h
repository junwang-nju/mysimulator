
#ifndef _Interaction_Pairwise_Shifted_FENE_H_
#define _Interaction_Pairwise_Shifted_FENE_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/shifted-fene.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void EFuncShiftedFENE(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncShiftedFENE);
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void GFuncShiftedFENE(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffShiftedFENE);
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void BFuncShiftedFENE(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothShiftedFENE);
  }

}

#endif
